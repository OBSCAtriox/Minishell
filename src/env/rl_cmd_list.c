/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_cmd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:45:00 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/25 03:05:00 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_builtin_cmds(t_cmd_list *list)
{
	static const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};
	int					i;

	i = 0;
	while (builtins[i])
	{
		if (!cmd_list_add(list, builtins[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	**build_cmd_list(void)
{
	t_cmd_list	list;
	char		*path;

	list.items = NULL;
	list.count = 0;
	list.cap = 0;
	if (!add_builtin_cmds(&list))
		return (free_doble_pointer(list.items), NULL);
	path = expand_variable("PATH", te()->envp);
	if (!add_path_cmds(path, &list))
		return (free_doble_pointer(list.items), NULL);
	return (list.items);
}
