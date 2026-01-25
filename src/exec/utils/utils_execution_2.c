/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:30:42 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/14 20:07:01 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_control	*tc(void)
{
	static t_control	control;

	return (&control);
}

void	inits_pipeline(t_data *dt, int *has_next, t_cmd ***cmdv)
{
	dt->i = 0;
	dt->fd[0] = -1;
	dt->fd[1] = -1;
	dt->temp_fd = -1;
	dt->fail_loop = FALSE;
	tc()->last_pid = -1;
	*cmdv = ms()->cmdv;
	*has_next = 1;
}

int	safe_fork(t_data *dt)
{
	dt->pid = fork();
	if (dt->pid < 0)
	{
		perror("fork");
		close_caller_pipe(dt);
		dt->fail_loop = TRUE;
		return (FALSE);
	}
	return (TRUE);
}

void	parent_step(t_data *dt)
{
	if (dt->fd[1] != -1)
		close(dt->fd[1]);
	if (dt->temp_fd != -1)
		close(dt->temp_fd);
	dt->temp_fd = dt->fd[0];
	dt->fd[0] = -1;
	dt->fd[1] = -1;
	tc()->last_pid = dt->pid;
}

void	close_all(int fd_1, int fd_2, int fd_3, int fd_4)
{
	if (fd_1 != -1)
		close(fd_1);
	if (fd_2 != -1)
		close(fd_2);
	if (fd_3 != -1)
		close(fd_3);
	if (fd_4 != -1)
		close(fd_4);
}
