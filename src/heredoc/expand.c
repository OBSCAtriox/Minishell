/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:10:08 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/18 05:09:03 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_line(char *line)
{
	t_data	dt;
	char	**exp;
	char	*line_out;

	inits_expand_line(&dt, line, &exp);
	exp_find_var(line, &dt.index_p, &dt.len_p);
	line_out = malloc(sizeof(char) * (dt.len + 1));
	if (!exp || !line_out || !dt.index_p || !dt.len_p)
		return (set_err(errno), free_fail_exp(exp, line_out, &dt, -1), NULL);
	while (dt.i < dt.len)
	{
		dt.l = 0;
		if (line[dt.j] == '$' && is_valid_character(line[dt.j + 1]))
		{
			while (exp[dt.k][dt.l])
				line_out[dt.i++] = exp[dt.k][dt.l++];
			dt.j += dt.len_p[dt.k] + 1;
			dt.k++;
		}
		else
			line_out[dt.i++] = line[dt.j++];
	}
	line_out[dt.len] = '\0';
	free_expand_line(&dt, &exp);
	return (line_out);
}

void	exp_find_var(char *line, int **index, int **len)
{
	t_data	dt;

	initis_exp_find_var(&dt, line);
	*index = malloc(sizeof(int) * dt.count);
	*len = malloc(sizeof(int) * dt.count);
	if (!*index || !*len)
		return (set_err(errno));
	while (line[dt.i])
	{
		dt.j = 1;
		if (line[dt.i] == '$' && line[dt.i + 1]
			&& is_valid_character(line[dt.i + 1]))
		{
			(*index)[dt.k] = dt.i + 1;
			while (line[dt.i + dt.j] && is_valid_character(line[dt.i + dt.j]))
			{
				dt.j++;
				if (line[dt.i + 1] == '?')
					break ;
			}
			(*len)[dt.k] = dt.j - 1;
			dt.k++;
		}
		dt.i++;
	}
}

char	**exp_str_var(char *line)
{
	t_data	dt;

	dt.len_p = NULL;
	dt.index_p = NULL;
	dt.size = count_var(line);
	exp_find_var(line, &dt.index_p, &dt.len_p);
	if (!dt.index_p || !dt.len_p)
		return (free_fail_exp(NULL, NULL, &dt, -1), NULL);
	dt.var = malloc(sizeof(char *) * (dt.size + 1));
	if (!dt.var)
		return (set_err(errno), free_fail_exp(NULL, NULL, &dt, -1), NULL);
	dt.i = 0;
	while (dt.i < dt.size)
	{
		dt.str = ft_substr(line, dt.index_p[dt.i], dt.len_p[dt.i]);
		if (!dt.str)
			return (free_fail_exp(dt.var, NULL, &dt, dt.i), NULL);
		dt.var[dt.i] = expand_vrb(dt.str);
		if (!dt.var[dt.i])
			return (free_fail_exp(dt.var, dt.str, &dt, dt.i), NULL);
		free_str(dt.str);
		dt.i++;
	}
	dt.var[dt.size] = NULL;
	return (free(dt.index_p), free(dt.len_p), dt.var);
}

int	count_len_exp(char *line)
{
	t_data	dt;

	dt.i = 0;
	dt.size = 0;
	dt.result = 0;
	while (line[dt.i])
	{
		dt.j = 1;
		if (line[dt.i] == '$' && is_valid_character(line[dt.i + 1]))
		{
			while (line[dt.i + dt.j] && is_valid_character(line[dt.i + dt.j]))
			{
				if (line[dt.i + dt.j] == '?')
				{
					dt.j = 2;
					break ;
				}
				dt.j++;
			}
			dt.size += dt.j;
		}
		dt.i++;
	}
	dt.result = len_expanded_var(line);
	return (ft_strlen(line) - dt.size + dt.result);
}

char	*expand_vrb(char *name)
{
	char	*vrb;

	vrb = NULL;
	if (name[0] == '?')
	{
		vrb = ft_itoa(te()->exit_code);
		if (vrb)
			return (vrb);
	}
	vrb = expand_variable(name, te()->envp);
	if (vrb)
		return (vrb);
	vrb = expand_variable(name, te()->l_var);
	if (vrb)
		return (vrb);
	return (ft_strdup(""));
}
