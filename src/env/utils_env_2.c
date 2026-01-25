/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:35:09 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/17 20:04:48 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_variable(char *name, char **env)
{
	int		index_variable;
	t_data	dt;
	char	*result;

	index_variable = find_variable(name, env);
	if (index_variable == -1)
		return (NULL);
	dt.temp = env[index_variable];
	dt.len = ft_strlen(dt.temp);
	dt.i = 0;
	dt.j = 0;
	while (dt.temp[dt.i] != '=')
		dt.i++;
	result = malloc(sizeof(char) * ((dt.len - dt.i) + 1));
	if (!result)
		return (set_err(errno), NULL);
	dt.i++;
	while (dt.temp[dt.i])
	{
		result[dt.j] = dt.temp[dt.i];
		dt.j++;
		dt.i++;
	}
	result[dt.j] = '\0';
	return (result);
}

void	create_local_variable(char *name, char *value)
{
	char	**l_var;

	l_var = te()->l_var;
	if (!te()->l_var)
	{
		l_var = malloc(sizeof(char *) * 2);
		if (!l_var)
			return (set_err(errno));
		l_var[0] = join3(name, EQUAL, value);
		if (!l_var[0])
		{
			free(l_var);
			l_var = NULL;
			return ;
		}
		l_var[1] = NULL;
		te()->l_var = l_var;
	}
}

char	*get_name_var(char *arg)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (set_err(errno), NULL);
	while (j < i)
		result[j++] = arg[k++];
	result[j] = '\0';
	return (result);
}

char	*get_value_var(char *arg)
{
	t_data	dt;
	char	*result;

	dt.len = ft_strlen(arg);
	dt.i = 0;
	while (arg[dt.i] && arg[dt.i] != '=')
		dt.i++;
	if (arg[dt.i] != '=')
		return (NULL);
	if (arg[dt.i + 1] == '\0')
		return (ft_strdup(""));
	result = malloc(sizeof(char) * ((dt.len - dt.i) + 1));
	if (!result)
		return (set_err(errno), NULL);
	dt.i++;
	dt.j = 0;
	while (arg[dt.i])
	{
		result[dt.j] = arg[dt.i];
		dt.j++;
		dt.i++;
	}
	result[dt.j] = '\0';
	return (result);
}
