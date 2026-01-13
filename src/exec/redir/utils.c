/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:20:15 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/12 20:25:17 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_dir(char *arg)
{
	struct stat	info;

	if (stat(arg, &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
			return (TRUE);
	}
	return (FALSE);
}

int	check_path(char *arg)
{
	if (access(arg, F_OK) != 0)
	{
		print_error(arg, "No such file or directory");
		tc()->exit_path = 127;
		return (FALSE);
	}
	if (is_dir(arg))
	{
		print_error(arg, "Is a directory");
		tc()->exit_path = 126;
		return (FALSE);
	}
	if (access(arg, X_OK) < 0)
	{
		print_error(arg, "Permission denied");
		tc()->exit_path = 126;
		return (FALSE);
	}
	return (TRUE);
}

void	close_fd_in(int fd, int *h_doc)
{
	if (fd != -1)
		close(fd);
	if (*h_doc != -1)
	{
		close(*h_doc);
		*h_doc = -1;
	}
}
