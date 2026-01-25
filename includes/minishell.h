/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:27:41 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/20 18:34:18 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# include "../libft/libft.h"
# include "colors.h"
# include "error.h"
# include <errno.h>
# include "exec.h"
# include "parsing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
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
	char			**var_exp;
	char			*oldpwd;
	char			*cwd;
	int				exit_code;
}					t_env;

typedef struct s_redir
{
	t_redir_type	type;
	int				fd_target;
	char			*path;
	int				hdoc_fd;
	int				quoted;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			**redir;
	int				is_builtin;
}					t_cmd;

typedef struct s_pipeline
{
	t_cmd			**cmdv;
}					t_pipeline;

typedef struct s_cmd_list
{
	char			**items;
	int				count;
	int				cap;
}					t_cmd_list;

t_env				*te(void);
t_pipeline			*ms(void);
int					redir(t_cmd *cmdv);
int					apply_redir_in(t_redir *redir);
int					apply_redir_out(t_redir *redir);
void				process_children(t_cmd *cmdv, int *fd, int temp_fd,
						int has_next);
void				safe_path(char **path, int *fd, int temp_fd, t_cmd *cmdv);
void				clean_redir(t_redir **redir);
int					verifications_after_malloc_struct(t_tokens *t);
int					add_check_vars(t_cmd **cmdv);
void				initis_main(int argc, char **argv, char **envp);
int					readline_and_check(void);
char				*build_prompt(void);
int					check_sigint(void);
int					empty_line(void);
void				exit_main(void);
void				init_readline_completion(void);
char				**build_cmd_list(void);
int					add_path_cmds(char *path, t_cmd_list *list);
int					cmd_list_grow(t_cmd_list *list);
int					cmd_list_add(t_cmd_list *list, const char *value);
int					check_if_redir(t_cmd **cmdv);
char				**isspace_split(char *str);
void				inits_pipeline(t_data *dt, int *has_next, t_cmd ***cmdv);

#endif
