/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:24 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/23 15:46:47 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ver_pos(t_split_var v, char *li, t_quote_split **head,
		t_quote_split **tail)
{
	if (v.i > v.st)
		create_spl_list(head, tail, ft_substr(li, v.st, v.i - v.st), NONE);
}

static t_quote_type	ver_type(char c)
{
	if (c == '"')
		return (DOUBLE);
	else if (c == '\'')
		return (SINGLE);
	else
		return (NONE);
}

static int	aux_ms_split(t_split_var *v, char *li)
{
	if (v->ty == NONE && li[v->i] == '$'
		&& (li[v->i + 1] == '"' || li[v->i + 1] == '\''))
	{
		if (v->i > v->st)
			create_spl_list(&v->head, &v->tail, ft_substr(li, v->st, (v->i
						- v->st)), v->ty);
		v->st = v->i + 1;
		v->i++;
		return (1);
	}
	return (0);
}

t_quote_split	*ms_split(char *li)
{
	t_split_var	v;

	init_split_vars(&v);
	while (li[v.i])
	{
		if (aux_ms_split(&v, li))
			continue ;
		else if (v.ty == NONE && ft_strchr("\"\'", li[v.i]))
		{
			if (v.i > v.st)
				create_spl_list(&v.head, &v.tail, ft_substr(li, v.st, (v.i
							- v.st)), v.ty);
			v.ty = ver_type(li[v.i]);
			v.st = v.i + 1;
		}
		else if (v.ty != NONE && ver_type(li[v.i]) == v.ty)
		{
			create_spl_list(&v.head, &v.tail, ft_substr(li, v.st, v.i - v.st),
				v.ty);
			v.ty = NONE;
			v.st = v.i + 1;
		}
		v.i++;
	}
	return (ver_pos(v, li, &v.head, &v.tail), v.head);
}
