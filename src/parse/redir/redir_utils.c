/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:36 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/12 18:38:37 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	r_ver_after_util(char c)
{
	if (c && c != '|' && !ft_strchr("<>", c))
		return (1);
	return (0);
}

int	r_ver_after(bool d_q, bool s_q, const char *li)
{
	int	i;

	i = 0;
	while (li[i])
	{
		quotes_ver(&d_q, &s_q, li[i]);
		if (ft_strchr("<>", li[i]) && !d_q && !s_q)
		{
			if (li[i + 1] == li[i])
				i += 2;
			else
				i++;
			if (li[i])
			{
				quotes_ver(&d_q, &s_q, li[i]);
				if (ms_isspaces(li[i]))
					i++;
				else
					return (r_ver_after_util(li[i]));
			}
		}
		i++;
	}
	return (1);
}

int	r_ver_synt(bool d_q, bool s_q, const char *li)
{
	int	i;

	i = 0;
	while (li[i])
	{
		quotes_ver(&d_q, &s_q, li[i]);
		if (ft_strchr("<>", li[i]) && !d_q && !s_q)
		{
			if (li[i] == '<' && li[i + 1] == '>')
				return (0);
			else if (li[i] == '>' && li[i + 1] == '<')
				return (0);
			else if (ft_strchr("<>", li[i + 1]) && ft_strchr("<>", li[i + 2]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	r_ver_bef_aft_pipe(bool d_q, bool s_q, const char *li)
{
	int	i;
	int	j;

	i = 0;
	while (li[i])
	{
		quotes_ver(&d_q, &s_q, li[i]);
		if (li[i] == '|' && !d_q && !s_q)
		{
			j = i - 1;
			while (j >= 0 && ms_isspaces(li[j]))
				j--;
			if (j < 0 || ft_strchr("<>", li[j]))
				return (0);
			j = i + 1;
			while (li[j] && ms_isspaces(li[j]))
				j++;
			if (!li[j] || ft_strchr("<>", li[j]))
				return (1);
		}
		i++;
	}
	return (1);
}
