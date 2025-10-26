#ifndef MINISHELL_H
#define MINISHELL_H

#include "exec.h"
#include "../libft/libft.h"

typedef enum e_redir_type { R_IN, R_OUT, R_APP, R_HDOC } 
t_redir_type;

typedef struct s_env
{
    char    **l_var;
    char    **envp;
    char    *oldpwd;
    int     exit_code;
}           t_env;

typedef struct s_redir {
    t_redir_type type;
    int          fd_target;     // 0 para input, 1 para output (ou outro)
    char        *path;          // para <, >, >>
    int          hdoc_fd;       // válido se HEREDOC
    int          quoted;        // 0 sem quotes, 1 para quotes
} t_redir;

typedef struct s_cmd {
    char   **argv;         // argv[0] é o comando (sem aspas)
    t_redir **redir;        // array de redireções
    int     is_builtin;    // 1 se echo/cd/pwd/export/unset/env/exit
} t_cmd;

typedef struct s_pipeline {
    t_cmd **cmdv;          // vetor de comandos (terminado por NULL)
} t_pipeline;


t_env  *te(void);
t_pipeline *tp(void);
int    redir(t_cmd *cmdv);
int apply_redir_in(t_redir *redir);
int apply_redir_out(t_redir *redir);
void    process_children(t_cmd *cmdv, int *fd, int temp_fd, int has_next);
void    safe_path(char **path, int *fd, int temp_fd, t_cmd *cmdv);
void    clean_redir(t_redir **redir);
#endif
