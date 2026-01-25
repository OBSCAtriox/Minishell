/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:40:28 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/20 17:38:51 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "stdbool.h"

# define MAX_PIPES 256
# define BUF_SIZE 100000

typedef enum e_token_type
{
	WORD,
	PR_IN,
	PR_OUT,
	PR_APP,
	PR_HDOC,
	PPIPE,
}							t_token_type;

typedef enum e_quote_type
{
	NONE,
	DOUBLE,
	SINGLE,
}							t_quote_type;

typedef struct s_tokens
{
	char					*value;
	int						quote;
	t_token_type			type;
	struct s_tokens			*next;
	struct s_tokens			*prev;
}							t_tokens;

typedef struct s_per_cmd_toks
{
	t_tokens				*cmdt;
	struct s_per_cmd_toks	*next;
}							t_per_cmd_tok;

typedef struct s_quote_split
{
	char					*str;
	t_quote_type			type;
	struct s_quote_split	*next;
	struct s_quote_split	*prev;
}							t_quote_split;

typedef struct s_split_var
{
	int						i;
	int						st;
	t_quote_split			*head;
	t_quote_split			*tail;
	t_quote_type			ty;
}							t_split_var;

typedef struct s_parse
{
	char					*line;
	int						n_cmd;
	int						n_pipes;
	t_tokens				*tok;
	t_quote_split			*sp;
	t_per_cmd_tok			*tl;
}							t_parse;

typedef struct s_vars
{
	int						i;
	int						y;
	bool					d_q;
	bool					s_q;
	int						buf_i;
	char					buf[BUF_SIZE];
}							t_vars;

typedef struct s_tok_split_vars
{
	t_per_cmd_tok			*head;
	t_per_cmd_tok			*tail;
	t_tokens				*start;
	t_tokens				*prev;
	t_tokens				*pipe;
}							t_tok_split_vars;

// Parse add_to/struct
// add_to_struct.c
void						add_to_struct(void);

// ver_tok_list_utils.c
void						redir_arr_malloc(int size, int i);
void						add_cmd_argv(t_per_cmd_tok *tl);

// ver_tok_list.c
int							if_redir(t_token_type type);

// Parse error
// error.c
void						ps_error(char *msg);

// Parse free_funcs
// free_ver1.c
void						free_split_list(t_quote_split **head);
void						free_all(char *msg, int i);
void						free_all_kill(void);

// free_ver2.c
void						free_list_of_tok_list(void);
void						free_tokens_arg(t_tokens **toks);

// Parse mallocs
// struct_mallocs.c
int							malloc_struct(void);
int							malloc_redir_struct(int cmd_i, int size);

// Parse quote_split
// ms_split_list.c
void						create_spl_list(t_quote_split **head,
								t_quote_split **tail, char *li,
								t_quote_type type);

// ms_split.c
t_quote_split				*ms_split(char *li);

// Parse redir
// redir_utils.c
int							r_ver_after(bool d_q, bool s_q, const char *li);
int							r_ver_synt(bool d_q, bool s_q, const char *li);
int							r_ver_bef_aft_pipe(bool d_q, bool s_q,
								const char *li);

// redir_ver_target.c
int							r_ver_midle(bool d_q, bool s_q, const char *li);
int							r_ver_start(const char *li);
int							r_ver_end(const char *li);
int							r_ver(const char *li);

// Parse token_split
// tok_split.c
t_per_cmd_tok				*tok_split(t_tokens *t);
void						aux_tok_split(t_tokens **start, t_tokens **pipe,
								t_tokens **prev, t_tokens **t);

// Parse tokens
// tokens_utils.c
void						buf_i_ver(t_tokens **head, t_tokens **tail,
								t_vars *v, bool yn);
void						quotes_ver(bool *d_quotes, bool *s_quotes, char c);
void						inc_i(int *i, int n);
t_tokens					*new_tok(char *value, int type);
bool						is_assignment(const char *s);

// tokens_utils2.c
void						remove_empty_tokens(t_tokens **head);
void						expand_quotes(t_quote_split *h, t_tokens *t);
void						ver_to_expand_helper2(t_tokens *t, char **words);

// tokens_ver.c
char						*ver_expand_h(t_quote_split *h);
char						**expand_then_split(t_quote_split *h, t_tokens *t);
void						replace_tok_with_words(t_tokens *tok, char **words);
void						ver_to_expand(t_tokens **t_head);
void						verify_contain_quote(t_tokens *t);

// tokens.c
void						create_token(t_tokens **head, t_tokens **tail,
								char *buffer, int buf_i);
void						token_list(const char *li);

// Parse utils
// init.c
t_parse						*ps(void);
void						init_token(t_vars *v);
void						init_s_var(t_vars *var);
void						init_split_vars(t_split_var *va);

// isspaces_split.c
char						**isspace_split(char *str);

// isspaces.c
int							ms_isspaces(char c);

// Parse
// pipeparse.c
void						num_pipes(const char *line);
int							pipe_ver_start(const char *line);
int							pipe_ver_end(const char *line);
int							pipe_ver_mid(const char *line);
int							ver_mid_help(const char *line, int i, int y);

// verifications.c
int							verify_whitespaces(char *line);
bool						quotes(const char *line);
int							verifications(const char *line);

// int					r_ver_pipe_util(bool d_q, bool s_q, const char *li);
// void						print_minishell_structs(int n);

#endif