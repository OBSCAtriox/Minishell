/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:41 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/12 18:38:37 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	init_tok_split_list(t_tok_split_vars *v, t_tokens *tok)
{
	v->head = NULL;
	v->tail = NULL;
	v->start = tok;
	v->prev = NULL;
}

static t_per_cmd_tok	*new_cmd_list(t_tokens *tok_slice)
{
	t_per_cmd_tok	*new;

	if (!tok_slice)
		return (NULL);
	new = malloc(sizeof(t_per_cmd_tok));
	if (!new)
		free_all(MALLOC_FAIL, 1);
	new->cmdt = tok_slice;
	new->next = NULL;
	return (new);
}

static void	add_list_to_list(t_per_cmd_tok **head, t_per_cmd_tok **tail,
		t_tokens *tok)
{
	t_per_cmd_tok	*new;

	new = new_cmd_list(tok);
	if (!new)
		free_all(MALLOC_FAIL, 1);
	if (!*head)
	{
		(*head) = new;
		(*tail) = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

t_per_cmd_tok	*tok_split(t_tokens *t)
{
	t_tok_split_vars	v;

	init_tok_split_list(&v, t);
	while (t)
	{
		if (t->type == PPIPE)
		{
			if (v.prev)
			{
				v.prev->next = NULL;
				add_list_to_list(&v.head, &v.tail, v.start);
			}
			aux_tok_split(&v.start, &v.pipe, &v.prev, &t);
			continue ;
		}
		v.prev = t;
		t = t->next;
	}
	if (v.start)
		add_list_to_list(&v.head, &v.tail, v.start);
	return (v.head);
}

void	aux_tok_split(t_tokens **start, t_tokens **pipe, t_tokens **prev,
		t_tokens **t)
{
	*pipe = *t;
	*t = (*t)->next;
	if (*t)
		(*t)->prev = NULL;
	*start = *t;
	if ((*pipe)->value)
		free((*pipe)->value);
	free(*pipe);
	*prev = NULL;
}
