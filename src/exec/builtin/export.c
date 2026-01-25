/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:17:39 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/18 04:57:34 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_export(char **argv)
{
	int	i;
	int	signaled_exit;

	i = 1;
	signaled_exit = FALSE;
	if (!argv || !argv[1])
		return (global_print());
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
		{
			if (aux_export(argv, i))
			{
				if (!signaled_exit)
					te()->exit_code = 0;
			}
			else
				return (cons_err("export"), FALSE);
		}
		else
			aux_export_two(argv[i], &signaled_exit);
		i++;
	}
	return (TRUE);
}

int	print_export(char **env)
{
	int	count;
	int	printed_count;
	int	*printed;
	int	next;

	if (!env || !*env)
		return (FALSE);
	count = size_vetor(env);
	printed = ft_calloc(count, sizeof(int));
	if (!printed)
		return (set_err(errno), FALSE);
	printed_count = 0;
	while (printed_count < count)
	{
		next = find_next_min(env, printed);
		if (next == -1)
			break ;
		print_export_line(env[next]);
		printed[next] = 1;
		printed_count++;
	}
	free(printed);
	return (TRUE);
}

int	is_valid_identifier(char *arg)
{
	int	first_character;
	int	other_character;
	int	len;

	if (!arg || arg[0] == '\0')
		return (FALSE);
	first_character = FALSE;
	other_character = FALSE;
	len = ft_strlen(arg);
	if (ft_isalpha(arg[0]) || arg[0] == '_')
		first_character = TRUE;
	other_character = valid_sec_character(arg);
	if (first_character && other_character && len > 1)
		return (TRUE);
	else if (first_character && len == 1)
		return (TRUE);
	return (FALSE);
}

int	export_variable(char *arg)
{
	int		index;
	char	*var;
	char	*name;
	char	*value;

	index = find_variable(arg, te()->l_var);
	if (index == -1)
	{
		if (!update_var_exp(arg))
			return (FALSE);
	}
	else
	{
		var = te()->l_var[index];
		name = get_name_var(var);
		value = get_value_var(var);
		if (!name || !value)
			return (free(name), free(value), FALSE);
		if (!env_set(name, value, te()->envp))
			return (free(name), free(value), FALSE);
		if (!remove_local_var(index))
			return (free(name), free(value), FALSE);
		return (free(name), free(value), TRUE);
	}
	return (TRUE);
}

int	aux_export(char **argv, int i)
{
	char	*name;
	char	*value;

	name = get_name_var(argv[i]);
	value = get_value_var(argv[i]);
	if (!name)
		return (free(name), free(value), FALSE);
	if (has_equal(argv[i]) && !value)
	{
		if (!env_set(name, "", te()->envp))
			return (free(name), free(value), FALSE);
	}
	else if (!has_equal(argv[i]) && !value)
	{
		if (!export_variable(name))
			return (free(name), free(value), FALSE);
	}
	else
	{
		if (!check_sum_and_set(name, value, te()->envp))
			return (free(name), free(value), FALSE);
		if (!remove_var_exp(find_variable(name, te()->var_exp)))
			return (free(name), free(value), FALSE);
	}
	return (free(name), free(value), TRUE);
}
