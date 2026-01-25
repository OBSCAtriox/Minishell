/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution_7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 22:23:17 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/24 22:23:18 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_var(char *name)
{
	char	*result;
	int		idx;

	idx = find_variable(name, te()->envp);
	if (idx != -1)
		result = ft_strdup(te()->envp[idx]);
	idx = find_variable(name, te()->var_exp);
	if (idx != -1)
		result = ft_strdup(te()->var_exp[idx]);
	idx = find_variable(name, te()->l_var);
	if (idx != -1)
		result = ft_strdup(te()->l_var[idx]);
	if (!result)
		return (NULL);
	return (result);
}

int	add_fallback_value(char *arg)
{
	int		i;
	int		size;
	char	**new_list;
	char	*var;

	var = get_var(arg);
	if (!arg || !var)
		return (FALSE);
	size = size_vetor(tc()->fallback_value_var);
	new_list = malloc(sizeof(char *) * (size + 2));
	if (!new_list)
		return (set_err(errno), FALSE);
	i = 0;
	while (i < size)
	{
		new_list[i] = tc()->fallback_value_var[i];
		i++;
	}
	new_list[i++] = var;
	new_list[i] = NULL;
	free(tc()->fallback_value_var);
	tc()->fallback_value_var = new_list;
	return (TRUE);
}

int	shell_level(void)
{
	int		index;
	int		value;
	char	*exp_value;
	char	*str_value;

	index = find_variable("SHLVL", te()->envp);
	if (index == -1)
	{
		if (!env_set("SHLVL", "1", te()->envp))
			return (FALSE);
		return (TRUE);
	}
	exp_value = expand_variable("SHLVL", te()->envp);
	if (!exp_value || !ft_isnumeric(exp_value))
	{
		env_set("SHLVL", "1", te()->envp);
		return (free(exp_value), FALSE);
	}
	value = ft_atoi(exp_value);
	value += 1;
	str_value = ft_itoa(value);
	if (!env_set("SHLVL", str_value, te()->envp))
		return (free(exp_value), free(str_value), FALSE);
	return (free(exp_value), free(str_value), TRUE);
}

int	fallback_fail(void)
{
	restore_vars();
	remove_vars_fallback();
	free_doble_pointer(tc()->fallback_value_var);
	tc()->fallback_value_var = NULL;
	return (FALSE);
}

void	restore_vars(void)
{
	int		i;
	char	*name;
	char	*value;

	if (!tc()->fallback_value_var)
		return ;
	i = 0;
	while (tc()->fallback_value_var[i])
	{
		name = get_name_var(tc()->fallback_value_var[i]);
		value = get_value_var(tc()->fallback_value_var[i]);
		if (!name || !value)
			return (free(name), free(value));
		call_update_var(name, value);
		free(name);
		free(value);
		i++;
	}
}
