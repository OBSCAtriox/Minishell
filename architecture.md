# Minishell Architecture

This document describes the architecture of the Minishell project (based on the current repository structure), focusing on **parsing** and **execution**.

---

## Overview

The main flow follows the classic shell loop:

1. **Initialization** (`initis_main`) — environment setup, `envp` copies, global state initialization.
2. **Interactive prompt** — prompt signal configuration (`setup_prompt_signal`).
3. **Input reading** — `readline_and_check()` builds a colored prompt via `build_prompt()` and reads input (Ctrl-D exits the shell, etc.).
4. **Pre-validations** — `check_sigint()`, `empty_line()`, `verify_whitespaces()`, `verifications()`.
5. **Parsing** — transforms `ps()->line` into a pipeline structure (`ms()->cmdv`).
6. **Execution** — runs builtins / external binaries with pipes and redirections (`execution()`).
7. **Cleanup** — frees all cycle-related resources (`free_all`) and returns to the prompt.

`main.c` relies on *singletons* to keep global state without exposing raw global variables:

- `te()` → `t_env` (environment state, exit code, cwd)
- `ms()` → `t_pipeline` (current pipeline)
- `ps()` → `t_parse` (parsing state, tokens, auxiliary lists)
- `tc()` → `t_control` (execution state: paths, pids, std clones, signals, etc.)

---

## Directory Organization

### Root
- `main.c` — main program loop.
- `src/utils_main.c` — utilities used by the main loop (readline integration).
- `src/utils_main_2.c` — prompt construction (`build_prompt()` and helpers).

### Includes
- `includes/minishell.h` — core structs (`t_cmd`, `t_redir`, `t_env`, `t_pipeline`).
- `includes/parsing.h` — parser-related types (`t_tokens`, `t_quote_split`, etc.).
- `includes/exec.h` — execution logic, builtins, redirections, heredoc, signals.
- `includes/colors.h` — ANSI color codes and readline-safe prompt constants.

### Parsing (`src/parse/`)
- `quote_split/` — splitting logic respecting quotes.
- `token_split/` and `tokens/` — token creation and management.
- `redir/` — redirection validation and handling.
- `mallocs/` — allocation of final execution structures (`ms()->cmdv`, redirs, etc.).
- `add_to_struct/` — builds `t_cmd` / `t_redir` from tokens.
- `error/` and `free_funcs/` — parser errors and cleanup.

### Execution (`src/exec/`)
- `path/` — PATH splitting and binary resolution.
- `redir/` — application of `<`, `>`, `>>` and file descriptor management.
- `builtin/` — builtin implementations.
- `error/` — error messages and mappings.
- `utils/` — execution helpers.

### Heredoc (`src/heredoc/`)
- `<<` logic, dedicated fork/pipe, and specific signal handling.

### Environment (`src/env/`)
- `envp` creation and copy, export/unset logic, local variables, etc.

---

## Core Data Structures

### `t_cmd` (single command)
- `argv` → argument vector ready for builtin or `execve`.
- `redir` → array of `t_redir*` associated with this command.
- `is_builtin` → flag used to choose the execution strategy.

### `t_redir` (redirection)
- `type` → `R_IN`, `R_OUT`, `R_APP`, `R_HDOC`.
- `path` → target file or heredoc delimiter (depending on implementation).
- `fd_target` / `hdoc_fd` → file descriptors needed to apply the redirection.
- `quoted` → indicates whether the heredoc delimiter was quoted (affects expansion).

### `t_pipeline` (entire command line)
- `cmdv` → array of `t_cmd*` (size = `ps()->n_cmd`).

### `t_parse` (parsing state)
- `line` → raw input line.
- `tok` → doubly-linked list of `t_tokens`.
- `tl` → list of per-command token lists (`t_per_cmd_tok`), split by pipes.
- helpers: `n_cmd`, `n_pipes`, `sp` (quote_split), etc.

### `t_control` (execution state)
Stores execution-related mutable state:
- standard input/output cloning and restoration
- resolved PATH entries
- `last_pid`, `num_cmd`, `in_parent`, `g_sig`, heredoc flags
- `last_err` / `err_printed` for consistent error reporting

---

## Parsing

The parser is responsible for:

- validating the input line (quotes, pipes, redirections)
- transforming the input into tokens
- performing expansions (`$VAR`, `$?`) while respecting quoting rules
- building the final execution structure (`ms()->cmdv`)

### 1) Initial Syntax Validation
`verifications()` centralizes the main rules, assisted by helper functions:

- pipes at start/end/middle (`pipe_ver_start`, `pipe_ver_end`, `pipe_ver_mid`)
- redirection rules (e.g. redirection without target)
- closed quotes (`quotes()`)
- invalid whitespace (`verify_whitespaces()`)

**Goal:** ensure that when `add_to_struct()` is reached, the input is already consistent.

---

### 2) Tokenization
Tokenization splits the input into:

- `WORD` (arguments)
- `PR_IN` (`<`), `PR_OUT` (`>`), `PR_APP` (`>>`), `PR_HDOC` (`<<`)
- `PPIPE` (`|`)

Typical flow:

- `ms_split()` / `quote_split` separates segments respecting quotes.
- `token_list()` builds the `t_tokens` list.
- `verify_contain_quote()` and `quotes_ver()` assist in quote validation.

---

### 3) Variable Expansion
Expansion occurs during parsing:

- `ver_to_expand()` identifies tokens that require expansion.
- `expand_then_split()` / `expand_quotes()` perform expansion and re-splitting if needed.
- `replace_tok_with_words()` replaces one token with multiple `WORD` tokens.
- `remove_empty_tokens()` removes tokens that became empty after expansion.

**Rules:**
- No expansion inside single quotes.
- Expansion is allowed inside double quotes.

---

### 4) Split by Commands (pipes)
Once the token list is ready:

- `tok_split()` splits the token list into a list of `t_per_cmd_tok`,
  each node representing a command separated by `PPIPE`.

This is the bridge between tokenization and final execution structures.

---

### 5) Final Structure Assembly (`ms()->cmdv`)
The last parsing step builds the pipeline consumed by the executor:

- `malloc_struct()` allocates `ms()->cmdv`.
- `malloc_redir_struct()` / `redir_arr_malloc()` allocate redirection arrays.
- `add_cmd_argv()` builds `argv` for each command.
- `add_to_struct()` populates `t_cmd` and `t_redir` structures.

At this point:
- `ps()->n_cmd` commands exist
- each command has a valid `argv`
- redirections are fully defined

---

## Execution

Execution consumes `ms()->cmdv` and applies:

- heredocs
- redirections
- pipes and forks
- builtins or `execve`
- waiting and exit status handling

### 0) Preparation
Typically includes:

- cloning shell standard FDs
- PATH splitting and caching
- command counters and indexes

---

### 1) Heredoc (`<<`)
Heredocs are resolved **before** pipeline execution because they may block input
and require specific signal handling.

Relevant functions:
- `heredoc()`, `mount_heredoc()`
- `read_heredoc()`
- `wait_heredoc()`

Result: a ready file descriptor stored in `t_redir`.

---

### 2) Pipes and Fork Loop
For each command:

- create a pipe if needed
- fork
- child: apply `dup2`, redirections, then execute
- parent: close unused FDs and prepare for next command

---

### 3) Redirections
Redirections are applied in the correct context:

- `<`, `>`, `>>` handled via `apply_redir_*`
- all FDs are closed after use to avoid leaks

---

### 4) Builtins (Parent vs Child)

Some builtins must execute in the **parent process** because they modify shell state:

- `cd`
- `export`
- `unset`
- `exit`

If a builtin appears inside a pipeline, it is executed in a child process to
preserve pipeline semantics.

---

### 5) External Commands
For non-builtins:

- binary path is resolved using PATH
- directories and permissions are checked
- `execve()` is called with `te()->envp`

---

### 6) Waiting and `$?`
- parent waits for children
- exit status is stored in `te()->exit_code`
- `$?` expansion uses this value

---

## Signals

Three main signal contexts exist:

1. **Prompt** — Ctrl-C clears the line and shows a new prompt.
2. **Heredoc** — Ctrl-C aborts heredoc without killing the shell.
3. **Execution** — parent and child use different signal behaviors.

---

## Memory and Ownership Rules

- All parsing-related allocations live for a single loop iteration.
- `free_all()` is the single cleanup point after execution.
- Environment data persists between iterations and is freed on exit.

---

## Responsibility Map

- `main.c` → main loop
- `src/parse/*` → validation, tokenization, expansion, struct building
- `src/heredoc/*` → heredoc logic and signals
- `src/exec/*` → pipes, fork, execve, builtins, redirections
- `src/env/*` → environment management
