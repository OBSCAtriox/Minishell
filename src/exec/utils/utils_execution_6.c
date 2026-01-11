/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:30:54 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/11 20:34:13 by thde-sou         ###   ########.fr       */
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
