/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_ver_target.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:38 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/20 20:25:16 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	r_ver_midle(bool d_q, bool s_q, const char *li)
{
	int	i;

	i = 0;
	while (li[i])
	{
		quotes_ver(&d_q, &s_q, li[i]);
		if (ft_strchr("<>", li[i]) && !d_q && !s_q)
		{
			if (ft_strchr("<>", li[i + 1]))
				i++;
			i++;
			while (li[i] && ms_isspaces(li[i]))
				i++;
			if (ft_strchr("<>", li[i]))
				return (0);
			continue ;
		}
		i++;
	}
	return (1);
}

int	r_ver_start(const char *li)
{
	int	i;

	i = 0;
	while (li[i])
	{
		if (ms_isspaces(li[i]))
			i++;
		else
		{
			if (ft_strchr("<>", li[i]))
			{
				if (li[i] == '<' && li[i + 1] == '<')
					break ;
				return (0);
			}
			break ;
		}
	}
	return (1);
}

int	r_ver_end(const char *li)
{
	int	i;

	i = ft_strlen(li) - 1;
	while (li[i])
	{
		if (ms_isspaces(li[i]))
			i--;
		else
		{
			if (ft_strchr("<>", li[i]))
				return (0);
			break ;
		}
	}
	return (1);
}

int	r_ver(const char *li)
{
	bool	d_q;
	bool	s_q;

	d_q = false;
	s_q = false;
	if (!r_ver_end(li) || !r_ver_after(d_q, s_q, li)
		|| !r_ver_synt(d_q, s_q, li) || !r_ver_bef_aft_pipe(d_q, s_q, li)
		|| !r_ver_midle(d_q, s_q, li))
		return (free_all(SYNT_ERR_R, 0), 0);
	return (1);
}
