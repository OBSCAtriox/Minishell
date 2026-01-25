/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:52 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/12 18:38:37 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	create_token(t_tokens **head, t_tokens **tail, char *buffer, int buf_i)
{
	t_tokens	*tok;

	tok = malloc(sizeof(t_tokens));
	if (!tok)
		free_all(MALLOC_FAIL, 1);
	buffer[buf_i] = '\0';
	tok->value = ft_strdup(buffer);
	if (!tok->value)
		free_all(MALLOC_FAIL, 1);
	tok->type = WORD;
	tok->next = NULL;
	tok->prev = NULL;
	if (*head == NULL)
	{
		*head = tok;
		*tail = tok;
	}
	else
	{
		tok->prev = *tail;
		(*tail)->next = tok;
		*tail = tok;
	}
}

static void	add_token(t_tokens **head, t_tokens **tail, char *sym,
		t_token_type type)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		free_all(MALLOC_FAIL, 1);
	new->value = ft_strdup(sym);
	if (!new->value)
		free_all(MALLOC_FAIL, 1);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		new->prev = *tail;
		(*tail)->next = new;
		*tail = new;
	}
}

static void	handle_symbols(t_tokens **head, t_tokens **tail, const char *li,
		int *i)
{
	if (li[*i] == '|')
		return (add_token(head, tail, "|", PPIPE), (*i)++, (void)(0));
	else if (li[*i] == '<')
	{
		if (li[*i + 1] == '<')
			return (add_token(head, tail, "<<", PR_HDOC), inc_i(i, 1),
				(void)(0));
		else
			return (add_token(head, tail, "<", PR_IN), inc_i(i, 0), (void)(0));
	}
	else if (li[*i] == '>')
	{
		if (li[*i + 1] == '>')
			return (add_token(head, tail, ">>", PR_APP), inc_i(i, 1),
				(void)(0));
		else
			return (add_token(head, tail, ">", PR_OUT), inc_i(i, 0), (void)(0));
	}
}

static void	token_help(t_tokens **head, t_tokens **tail, const char *li)
{
	t_vars	v;

	init_token(&v);
	while (li[v.i])
	{
		quotes_ver(&v.d_q, &v.s_q, li[v.i]);
		if (isspace(li[v.i]) && !v.d_q && !v.s_q)
		{
			buf_i_ver(head, tail, &v, true);
			v.i++;
		}
		else if ((ft_strchr("><|", li[v.i])) && !v.d_q && !v.s_q)
		{
			buf_i_ver(head, tail, &v, true);
			handle_symbols(head, tail, li, &v.i);
		}
		else
			v.buf[v.buf_i++] = li[v.i++];
	}
	buf_i_ver(head, tail, &v, false);
	ft_bzero(v.buf, ft_strlen(v.buf));
}

void	token_list(const char *li)
{
	t_tokens	*head;
	t_tokens	*tail;

	head = NULL;
	tail = NULL;
	token_help(&head, &tail, li);
	verify_contain_quote(head);
	ps()->tok = head;
}
