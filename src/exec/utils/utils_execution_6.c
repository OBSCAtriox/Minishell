/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:30:54 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/14 18:16:59 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	process_fail(int *fd, int temp_fd, char **path)
{
	close_all(fd[0], fd[1], temp_fd, -1);
	clean_redir_fd();
	cleanup();
	free(*path);
	exit(1);
}

void	close_caller_pipe(t_data *dt)
{
	if(dt->fd[0] != -1)
		close(dt->fd[0]);
	if(dt->fd[1] != -1)
		close(dt->fd[1]);
}

int	safe_pipe(t_data *dt)
{
	if (dt->i < tc()->num_cmd - 1)
	{
		if (pipe(dt->fd) == -1)
		{
			perror("pipe");
			close_caller_pipe(dt);
			dt->fail_loop = TRUE;
			return (FALSE);
		}
	}
	return (TRUE);
}
