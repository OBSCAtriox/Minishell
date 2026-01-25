/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:45 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/12 18:38:37 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	buf_i_ver(t_tokens **head, t_tokens **tail, t_vars *v, bool yn)
{
	if (v->buf_i > 0)
		create_token(head, tail, v->buf, v->buf_i);
	if (yn)
		v->buf_i = 0;
}

void	quotes_ver(bool *d_quotes, bool *s_quotes, char c)
{
	if (c == '\'' && !*d_quotes)
		*s_quotes = !*s_quotes;
	else if (c == '"' && !*s_quotes)
		*d_quotes = !*d_quotes;
}

void	inc_i(int *i, int n)
{
	if (n == 1)
		(*i) += 2;
	else
		(*i)++;
}

t_tokens	*new_tok(char *value, int type)
{
	t_tokens	*t;

	t = malloc(sizeof(t_tokens));
	if (!t)
		free_all(MALLOC_FAIL, 1);
	t->value = value;
	t->type = type;
	t->next = NULL;
	t->prev = NULL;
	return (t);
}

bool	is_assignment(const char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (false);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (s[i] == '=');
}
