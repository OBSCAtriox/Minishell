/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:24:24 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/24 21:16:20 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define FALSE 0
# define TRUE 1
# define EQUAL "="
# define BAR "/"
# define MSG_HEREDOC "warning: here-document delimited by end-of-file (wanted `"

typedef struct s_data
{
	pid_t	pid;
	int		fd[2];
	int		temp_fd;
	int		fail_loop;
	int		result;
	int		count;
	int		index;
	int		size;
	int		len;
	char	*str;
	char	*temp;
	char	**env;
	char	**var;
	int		*index_p;
	int		*len_p;
	int		i;
	int		j;
	int		k;
	int		l;
}			t_data;

typedef struct s_control
{
	int		exit_path;
	pid_t	last_pid;
	int		num_cmd;
	int		num_redr;
	int		signaled_heredoc;
	int		hdoc_wfd;
	int		fd_stdout;
	int		fd_stdin;
	int		in_parent;
	char	**paths;
	char	**fallback_vars;
	char	**fallback_value_var;
	int		g_sig;
	int		sum_export;
	int		last_err;
	int		err_printed;
}			t_control;

t_control	*tc(void);
int			size_vetor(char **vetor);
int			mount_envp(char **envp);
void		free_vetor_failed(char ***vetor, int i);
int			builtin_cd(char **argv);
int			find_variable(char *name, char **env);
char		*join3(char *s1, char *s2, char *s3);
void		free_doble_pointer(char **p);
int			update_variable(char *name, char *value, char **env);
int			env_set(char *name, char *value, char **env);
void		print_error(char *comand, char *msg);
void		error_cd(char *arg);
int			builtin_echo(char **argv);
int			builtin_pwd(void);
char		*expand_variable(char *name, char **env);
int			print_export(char **env);
int			find_next_min(char **env, int *printed);
int			ft_strcmp_var(const char *s1, const char *s2);
void		print_export_line(char *env);
int			builtin_export(char **argv);
void		create_local_variable(char *name, char *value);
int			is_valid_identifier(char *arg);
char		*get_name_var(char *arg);
char		*get_value_var(char *arg);
int			has_equal(char *arg);
int			export_variable(char *arg);
int			re_mount_locar_var(char **envp);
int			create_new_local_var(char *name, char *value);
int			remove_env_var(int index);
int			builtin_unset(char **argv);
int			skip_var_dell(int index, int *i);
int			remove_local_var(int index);
int			builtin_env(void);
int			builtin_exit(char **arg);
void		cleanup(void);
char		*get_target(char **arg);
void		free_cd(char **new_pwd, char **target, char **old_pwd, int err);
void		exp_find_var(char *line, int **index, int **len);
int			count_var(char *line);
char		**exp_str_var(char *line);
int			count_len_exp(char *line);
void		free_str(void *p1);
int			len_expanded_var(char *line);
char		*expand_line(char *line);
int			is_valid_character(char c);
void		inits_expand_line(t_data *dt, char *line, char ***exp);
void		initis_exp_find_var(t_data *dt, char *line);
void		free_expand_line(t_data *dt, char ***exp);
int			heredoc(void);
int			mount_heredoc(int idx_cmd, int idx_rdir);
void		read_heredoc(int idx_cmd, int idx_rdir, int *fd, char *delim);
void		write_line(int quoted, char *line, int fd);
void		wait_heredoc(pid_t pid, int *fd);
void		close_fd_redir(void);
void		sigint_hdoc(int sig);
void		setup_heredoc_signals(int fd);
void		count_cmd(void);
void		execution(void);
int			call_builtin(char **argv);
int			restore_std(void);
int			clone_std(void);
int			splited_path(void);
char		*find_bin_path(char *arg);
char		*path_to_binary(char *arg);
int			builtin_in_parent_process(void);
int			safe_fork(t_data *dt);
void		parent_step(t_data *dt);
void		close_all(int fd_1, int fd_2, int fd_3, int fd_4);
int			make_dup_pipe(int *fd, int temp_fd, int has_next);
void		check_last_comand(t_data dt, int *has_next);
int			is_dir(char *arg);
int			check_path(char *arg);
void		wait_for_children(pid_t last_pid);
void		failed_cd(char **new_pwd, char **target, char **old_pwd);
int			aux_export(char **argv, int i);
int			aux_unset(char **argv, int i);
void		free_pipeline(void);
int			has_new_line(char *arg);
void		print_echo(char **argv, int i, int printed);
void		setup_prompt_signal(void);
void		sigint_prompt(int sig);
void		setup_exec_parent_signals(void);
void		setup_exec_child_signals(void);
int			is_builtin(const char *command, const char *name);
int			check_builtin(char *argv);
void		process_builtin(char **argv, char *path);
void		update_local_var(char *name, char *value);
char		*expand_vrb(char *name);
int			update_var_exp(char *name);
int			re_mount_var_exp(char **envp);
int			create_new_var_exp(char *name);
void		create_var_exp(char *name);
int			remove_var_exp(int index);
void		call_update_var(char *name, char *value);
int			valid_sec_character(char *arg);
int			check_sum_and_set(char *name, char *value, char **env);
int			not_sum(char *name, char *value, char **env, int *added);
void		check_sum_local_var(char *name, char *value);
int			check_number(char *arg);
int			shell_level(void);
int			inits_min_var(void);
void		clean_redir_fd(void);
int			local_var(char *argv);
void		set_cwd(void);
void		update_argv(char **argv);
int			copy_name_vetor(char ***dest, char **src);
void		add_fallback_var(char *arg);
void		remove_vars_fallback(void);
void		aux_export_two(char *arg, int *signaled_exit);
void		exit_heredoc(int fd_1);
int			inits_var_exp(t_data *dt);
int			global_print(void);
void		process_fail(int *fd, int temp_fd, char **path);
void		setup_exec_builtin_signals(void);
void		define_limits_exit(unsigned long long *limit, int sign);
void		print_exit(void);
void		close_fd_in(int fd, int *h_doc);
void		free_fail_exp(char **db_ptr, char *ptr, t_data *dt, int idx);
void		close_caller_pipe(t_data *dt);
int			safe_pipe(t_data *dt);
int			safe_waitpid_exec(pid_t *wpid, int *status);
int			safe_waitpid_hdoc(pid_t pid, int *status);
void		set_err(int err);
void		cons_err(char *command);
int			copy_envp(char **envp);
int			aux_cd(char *new_pwd, char *old_pwd, char *target);
void		print_cd_back(char **arg, char *target);
void		print_error_hdoc(char *delim);
int			check_if_exist_vars(char *arg);
int			add_fallback_value(char *arg);
void		restore_vars(void);
char		*get_var(char *name);
int			fallback_fail(void);

#endif
