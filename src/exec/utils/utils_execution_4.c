/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:30:48 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/24 21:40:19 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_sum_local_var(char *name, char *value)
{
	char	*new_value;
	char	*old_value;
	int		index;

	if (tc()->sum_export)
	{
		index = find_variable(name, te()->l_var);
		if (index == -1)
		{
			create_local_variable(name, value);
			return ;
		}
		old_value = expand_variable(name, te()->l_var);
		new_value = join3(old_value, value, NULL);
		if (!new_value || !old_value)
			return ;
		update_local_var(name, new_value);
		free(old_value);
		free(new_value);
	}
	else
		update_local_var(name, value);
}

void	call_update_var(char *name, char *value)
{
	int	idx;

	idx = find_variable(name, te()->envp);
	if (idx != -1)
	{
		if (!check_sum_and_set(name, value, te()->envp))
			return ;
		idx = find_variable(name, te()->l_var);
		if (idx != -1)
			remove_local_var(idx);
		idx = find_variable(name, te()->var_exp);
		if (idx != -1)
			remove_var_exp(idx);
		return ;
	}
	idx = find_variable(name, te()->var_exp);
	if (idx != -1)
	{
		if (!check_sum_and_set(name, value, te()->envp))
			return ;
		remove_var_exp(idx);
		return ;
	}
	check_sum_local_var(name, value);
}

static int	process_var_assignment(char *arg, char **argv)
{
	char	*name;

	if (!is_valid_identifier(arg) || !has_equal(arg))
		return (fallback_fail());
	name = get_name_var(arg);
	if (!name)
		return (fallback_fail());
	if (check_if_exist_vars(arg))
	{
		if (!add_fallback_value(name))
			return (free(name), fallback_fail());
	}
	else
		add_fallback_var(name);
	free(name);
	if (!local_var(arg))
		return (fallback_fail());
	update_argv(argv);
	return (TRUE);
}

int	add_check_vars(t_cmd **cmdv)
{
	char	**argv;

	argv = cmdv[0]->argv;
	if (!argv)
		return (FALSE);
	while (argv[0])
		if (!process_var_assignment(argv[0], argv))
			return (FALSE);
	return (TRUE);
}

int	check_if_redir(t_cmd **cmdv)
{
	char	**argv;
	t_redir	**redr;

	argv = cmdv[0]->argv;
	redr = cmdv[0]->redir;
	if (!argv || !argv[0])
	{
		if (!redr)
			return (te()->exit_code = 0, TRUE);
		clone_std();
		if (!redir(cmdv[0]))
		{
			restore_std();
			return (te()->exit_code = 1, TRUE);
		}
		restore_std();
		return (te()->exit_code = 0, TRUE);
	}
	return (FALSE);
}
