/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:30:37 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/11 20:30:38 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	clean_redir_fd(void)
{
	t_cmd	**cmdv;
	t_redir	**redir;
	int		i;

	cmdv = ms()->cmdv;
	if (!cmdv)
		return ;
	i = 0;
	while (cmdv[i])
	{
		redir = cmdv[i]->redir;
		if (redir)
		{
			clean_redir(redir);
			cmdv[i]->redir = NULL;
		}
		i++;
	}
}
