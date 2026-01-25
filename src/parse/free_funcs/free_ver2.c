/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ver2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:16 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/12 18:38:37 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_list_of_tok_list(void)
{
	t_per_cmd_tok	*tmp;
	t_per_cmd_tok	*head;

	head = ps()->tl;
	while (head)
	{
		tmp = head->next;
		free_tokens_arg(&head->cmdt);
		free(head);
		head = tmp;
	}
	ps()->tl = NULL;
}

void	free_tokens_arg(t_tokens **toks)
{
	t_tokens	*tmp;

	while (*toks)
	{
		tmp = (*toks)->next;
		if ((*toks)->value)
		{
			free((*toks)->value);
			(*toks)->value = NULL;
		}
		free(*toks);
		*toks = tmp;
	}
	*toks = NULL;
}
