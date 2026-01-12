/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_mallocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:18 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/12 18:38:37 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	malloc_struct(void)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	ms()->cmdv = ft_calloc(ps()->n_cmd + 1, sizeof(t_cmd *));
	if (!ms()->cmdv)
		free_all(MALLOC_FAIL, 1);
	while (i < ps()->n_cmd)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			free_all(MALLOC_FAIL, 1);
		ms()->cmdv[i] = cmd;
		i++;
	}
	ms()->cmdv[i] = NULL;
	return (1);
}

int	malloc_redir_struct(int cmd_i, int size)
{
	int		i;
	t_redir	**redir;
	t_redir	**new_redir;
	t_redir	*node;

	new_redir = ft_calloc(size + 1, sizeof(t_redir *));
	if (!new_redir)
		free_all(MALLOC_FAIL, 1);
	ms()->cmdv[cmd_i]->redir = new_redir;
	redir = new_redir;
	i = 0;
	while (i < size)
	{
		node = ft_calloc(1, sizeof(t_redir));
		if (!node)
			free_all(MALLOC_FAIL, 1);
		redir[i] = node;
		i++;
	}
	return (1);
}
