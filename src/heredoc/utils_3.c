/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:10:23 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/13 22:15:32 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_heredoc(int fd_1)
{
	close(fd_1);
	cleanup();
	exit(0);
}

void	free_fail_expand(char **db_ptr, char *ptr, t_data *dt, int idx)
{
	if (db_ptr)
	{
		if (idx >= 0)
			free_vetor_failed(db_ptr, idx);
		else
			free_doble_pointer(db_ptr);
	}
	if (ptr)
		free(ptr);
	if (dt->len_p)
		free(dt->len_p);
	if (dt->index_p)
		free(dt->index_p);
}
