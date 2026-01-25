/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:34:46 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/20 16:53:09 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_redir_type	redir_conv(t_token_type type)
{
	if (type == PR_APP)
		return (R_APP);
	else if (type == PR_HDOC)
		return (R_HDOC);
	else if (type == PR_IN)
		return (R_IN);
	else if (type == PR_OUT)
		return (R_OUT);
	return (0);
}

static void	ver_hdoc_and_quoted(t_tokens *t, int i, int y)
{
	if (t->type != WORD)
	{
		ms()->cmdv[i]->redir[y]->hdoc_fd = -1;
		ms()->cmdv[i]->redir[y]->type = redir_conv(t->type);
		if (t->type == PR_HDOC)
		{
			if (t->next && t->next->quote)
				ms()->cmdv[i]->redir[y]->quoted = 1;
			else
				ms()->cmdv[i]->redir[y]->quoted = 0;
		}
	}
}

static int	count_redirs(t_tokens *cmdt)
{
	int	count;

	count = 0;
	while (cmdt)
	{
		if (cmdt->type != WORD && cmdt->type != PPIPE)
			count++;
		cmdt = cmdt->next;
	}
	return (count);
}

static void	add_redirs(t_tokens *t, t_per_cmd_tok *tl, int i)
{
	int	y;

	y = 0;
	if (tl->cmdt->type == WORD)
		t = t->next;
	while (t)
	{
		if (t->type != WORD && t->next && t->next->type == WORD)
		{
			ms()->cmdv[i]->redir[y]->path = ft_strdup(t->next->value);
			if (!ms()->cmdv[i]->redir[y]->path)
				free_all(MALLOC_FAIL, 1);
			if (t->type == PR_IN || t->type == PR_HDOC)
				ms()->cmdv[i]->redir[y]->fd_target = 0;
			else if (t->type == PR_OUT || t->type == PR_APP)
				ms()->cmdv[i]->redir[y]->fd_target = 1;
			ver_hdoc_and_quoted(t, i, y);
			y++;
		}
		t = t->next;
	}
}

void	add_to_struct(void)
{
	t_vars			v;
	t_per_cmd_tok	*tmp;

	init_s_var(&v);
	tmp = ps()->tl;
	if (!tmp)
		return ;
	while (ms()->cmdv[v.i])
	{
		malloc_redir_struct(v.i, count_redirs(tmp->cmdt));
		add_redirs(tmp->cmdt, tmp, v.i);
		v.i++;
		tmp = tmp->next;
	}
}
