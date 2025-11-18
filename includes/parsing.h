#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "stdbool.h"
# include <readline/history.h>
# include <readline/readline.h>

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
}					t_token_type;

typedef enum e_quote_type
{
	NONE,
	DOUBLE,
	SINGLE,
} t_quote_type;

typedef struct s_tokens
{
	char			*value;
	t_token_type	type;
	struct s_tokens	*next;
	struct s_tokens *prev;
}					t_tokens;

typedef struct s_quote_split
{
	char *str;
	t_quote_type type;
	struct s_quote_split *next;
	struct s_quote_split *prev;
} t_quote_split;

typedef struct s_split_var
{
	int i;
	int st;
	t_quote_split *head;
	t_quote_split *tail;
	t_quote_type ty;
} t_split_var;

typedef struct s_parse
{
	char			*line;
	int				n_cmd;
	int				n_pipes;
	t_tokens		*tok;
	t_quote_split	*sp;
}					t_parse;

typedef struct s_vars
{
	int i;
	int y;
	bool d_q;
	bool s_q;
} 					t_vars ;

void	free_split_list(t_quote_split **head);
void				free_all(char *msg, int i);
void				num_pipes(const char *line);
t_parse				*ps(void);
t_quote_split	*ms_split(char *li);
int					ms_isspaces(char c);
void				ps_error(char *msg);
int					pipe_ver_end(const char *line);
int					pipe_ver_start(const char *line);
int					pipe_ver_mid(const char *line);
int					ver_mid_help(const char *line, int i, int y);
int					verifications(const char *line);
int					malloc_struct(void);
bool				quotes(const char *line);
void				create_token(t_tokens **head, t_tokens **tail, char *buffer,
						int buf_i);
void				buf_i_ver(t_tokens **head, t_tokens **tail, char *buf,
						int *buf_i, bool yn);

void				quotes_ver(bool *d_quotes, bool *s_quotes, char c);
void				token_list(const char *li);
void    ver_to_expand(t_tokens *t);
void	init_s_var(t_vars *var);
void				create_token(t_tokens **head, t_tokens **tail, char *buffer,
						int buf_i);
						void    create_spl_list(t_quote_split **head, t_quote_split **tail, char *li, t_quote_type type);
void				inc_i(int *i, int n);
void	init_split_vars(t_split_var *va);
void				init_token(int *i, int *buf_i, bool *d_q, bool *s_q);

int					r_ver_bef_aft_pipe(bool d_q, bool s_q, const char *li);
//int					r_ver_pipe_util(bool d_q, bool s_q, const char *li);
int					r_ver_after(bool d_q, bool s_q, const char *li);
int					r_ver_synt(bool d_q, bool s_q, const char *li);
int					r_ver_start(const char *li);
int					r_ver_end(const char *li);
int					r_ver(const char *li);

#endif