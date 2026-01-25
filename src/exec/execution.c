/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:35:27 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/20 22:11:51 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_in_parent_process(void)
{
	if (tc()->num_cmd == 1 && ms()->cmdv[0]->is_builtin)
	{
		tc()->in_parent = TRUE;
		clone_std();
		if (!redir(ms()->cmdv[0]))
		{
			restore_std();
			te()->exit_code = 1;
			return (TRUE);
		}
		if (!call_builtin(ms()->cmdv[0]->argv))
			te()->exit_code = 1;
		return (restore_std(), TRUE);
	}
	else if (tc()->num_cmd == 1 && !ms()->cmdv[0]->is_builtin)
	{
		if (check_if_redir(ms()->cmdv))
			return (TRUE);
		if (add_check_vars(ms()->cmdv))
		{
			free_doble_pointer(tc()->fallback_vars);
			return (tc()->fallback_vars = NULL, TRUE);
		}
	}
	return (FALSE);
}

void	process_builtin(char **argv, char *path)
{
	setup_exec_builtin_signals();
	tc()->in_parent = FALSE;
	if (!call_builtin(argv))
	{
		free(path);
		cleanup();
		exit(127);
	}
	free(path);
	cleanup();
	exit(0);
}

int	exec_pipeline(void)
{
	t_data	dt;
	t_cmd	**cmdv;
	int		has_next;

	inits_pipeline(&dt, &has_next, &cmdv);
	while (cmdv[dt.i])
	{
		check_last_comand(dt, &has_next);
		if (!safe_pipe(&dt))
			break ;
		if (!safe_fork(&dt))
			break ;
		if (dt.pid == 0)
			process_children(cmdv[dt.i], dt.fd, dt.temp_fd, has_next);
		parent_step(&dt);
		dt.i++;
	}
	if (dt.temp_fd != -1)
		close(dt.temp_fd);
	wait_for_children(tc()->last_pid);
	if (dt.fail_loop)
		return (FALSE);
	return (TRUE);
}

void	process_children(t_cmd *cmdv, int *fd, int temp_fd, int has_next)
{
	char	**envp;
	char	*path;

	setup_exec_child_signals();
	envp = te()->envp;
	safe_path(&path, fd, temp_fd, cmdv);
	if (!make_dup_pipe(fd, temp_fd, has_next))
		process_fail(fd, temp_fd, &path);
	if (!redir(cmdv))
		process_fail(fd, temp_fd, &path);
	close_all(fd[0], fd[1], temp_fd, -1);
	clean_redir_fd();
	if (!cmdv->argv || !cmdv->argv[0])
		return (cleanup(), exit(0));
	if (check_builtin(cmdv->argv[0]))
		process_builtin(cmdv->argv, path);
	execve(path, cmdv->argv, envp);
	perror(cmdv->argv[0]);
	if (path)
		free(path);
	cleanup();
	exit(127);
}

void	execution(void)
{
	count_cmd();
	tc()->sum_export = FALSE;
	if (!heredoc())
	{
		setup_prompt_signal();
		free_pipeline();
		return ;
	}
	if (builtin_in_parent_process())
	{
		setup_prompt_signal();
		tc()->sum_export = FALSE;
		free_pipeline();
		return ;
	}
	setup_exec_parent_signals();
	if (!exec_pipeline())
		te()->exit_code = 1;
	setup_prompt_signal();
	free_pipeline();
}
