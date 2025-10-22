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

typedef struct s_parse
{
	int				*p_pipe;
	char			*line;
	int				n_cmd;
	int				n_pipes;
}					t_parse;

typedef struct s_tokens
{
	char			*value;
	t_token_type	type;
	struct s_tokens	*next;
}					t_tokens;

void				free_all(char *msg);
void				num_pipes(const char *line);
t_parse				*ps(void);
int					ms_isspaces(char c);
void				ps_error(char *msg);
int					pipe_ver_end(const char *line);
int					pipe_ver_start(const char *line);
int					pipe_ver_mid(const char *line);
int					pipe_ver_mid_help(const char *line, int i, int y);
int					verifications(const char *line);
int					malloc_struct(void);
bool				quotes(const char *line);
void				free_all(char *msg);
void				create_token(t_tokens **head, t_tokens **tail, char *buffer,
						int buf_i);
void				buf_i_ver(t_tokens **head, t_tokens **tail, char *buf,
						int *buf_i, bool yn);
void				quotes_ver(bool *d_quotes, bool *s_quotes, char c);
t_tokens			*token_list(const char *li);
void	create_token(t_tokens **head, t_tokens **tail, char *buffer, int buf_i);
void	inc_i(int *i, int n);

#endif