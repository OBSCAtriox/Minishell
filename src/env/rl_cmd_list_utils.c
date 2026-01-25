/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_cmd_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:45:00 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/25 19:45:00 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cmd_list_contains(char **list, const char *value)
{
	int	i;

	if (!list || !value)
		return (FALSE);
	i = 0;
	while (list[i])
	{
		if (ft_strcmp(list[i], value) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	cmd_list_grow(t_cmd_list *list)
{
	char	**new_list;
	int		new_cap;
	int		i;

	new_cap = 16;
	if (list->cap > 0)
		new_cap = list->cap * 2;
	new_list = ft_calloc(sizeof(char *), (new_cap + 1));
	if (!new_list)
		return (FALSE);
	i = 0;
	while (list->items && list->items[i])
	{
		new_list[i] = list->items[i];
		i++;
	}
	free(list->items);
	list->items = new_list;
	list->cap = new_cap;
	return (TRUE);
}

int	cmd_list_add(t_cmd_list *list, const char *value)
{
	if (cmd_list_contains(list->items, value))
		return (TRUE);
	if (list->count >= list->cap && !cmd_list_grow(list))
		return (FALSE);
	list->items[list->count] = ft_strdup(value);
	if (!list->items[list->count])
		return (FALSE);
	list->count++;
	list->items[list->count] = NULL;
	return (TRUE);
}
