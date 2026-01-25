/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ver_tok_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:34:54 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/20 17:03:18 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* int	count_words(t_tokens *t)
{
	int	count;

	count = 0;
	while (t)
	{
		if (t->type == WORD)
			count++;
		t = t->next;
	}
	return (count);
} */

int	if_redir(t_token_type type)
{
	if (type != WORD && type != PPIPE)
		return (1);
	return (0);
}

/* void	num_redir_alloc(t_tokens *tmp)
{
	int	count;
	int	i;

	i = 0;
	while (tmp->next && ms()->cmdv[i])
	{
		count = 0;
		while (tmp->type != PPIPE && tmp->type != WORD)
		{
			if (tmp->type == PR_HDOC || tmp->type == PR_IN
				|| tmp->type == PR_OUT || tmp->type == PR_APP)
				count++;
			tmp = tmp->next;
		}
		if (count != 0)
			redir_arr_malloc(count, i);
		i++;
	}
} */
