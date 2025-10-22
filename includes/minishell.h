#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "colors.h"
# include "error.h"
# include "exec.h"
# include "parsing.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APP,
	R_HDOC
}					t_redir_type;

typedef struct s_env
{
	char			**l_var;
	char			**envp;
	char			*oldpwd;
}					t_env;

typedef struct s_redir
{
	t_redir_type	type;
	int fd_target; // 0 para input, 1 para output (ou outro)
	char *path;    // para <, >, >>
	int hdoc_fd;   // válido se HEREDOC
	int				quoted;
}					t_redir;

typedef struct s_cmd
{
	char **argv;    // argv[0] é o comando (sem aspas)
	t_redir *redir; // lista de redireções
	int is_builtin; // 1 se echo/cd/pwd/export/unset/env/exit
}					t_cmd;

typedef struct s_pipeline
{
	t_cmd **cmdv; // vetor de comandos (terminado por NULL)
}					t_pipeline;

t_env				*te(void);
t_pipeline			*ms(void);
t_pipeline			*tp(void);

#endif
