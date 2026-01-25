/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:31:03 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/17 22:44:27 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	not_sum(char *name, char *value, char **env, int *added)
{
	int	index;

	*added = FALSE;
	index = find_variable(name, env);
	if (index == -1 && tc()->sum_export)
	{
		if (!env_set(name, value, env))
			return (FALSE);
		*added = TRUE;
		tc()->sum_export = FALSE;
	}
	return (TRUE);
}

int	check_sum_and_set(char *name, char *value, char **env)
{
	char	*new_value;
	char	*old_value;
	int		added;

	if (!not_sum(name, value, env, &added))
		return (FALSE);
	if (tc()->sum_export && !added)
	{
		old_value = expand_variable(name, env);
		new_value = join3(old_value, value, NULL);
		if (!new_value || !old_value)
			return (FALSE);
		if (!env_set(name, new_value, env))
			return (free(old_value), free(new_value), FALSE);
		free(old_value);
		free(new_value);
	}
	else if (!tc()->sum_export && !added)
	{
		if (!env_set(name, value, env))
			return (FALSE);
	}
	return (TRUE);
}

void	aux_export_two(char *arg, int *signaled_exit)
{
	write(2, "export: ", 8);
	print_error(arg, "not a valid identifier");
	tc()->err_printed = 1;
	te()->exit_code = 1;
	*signaled_exit = TRUE;
}

int	global_print(void)
{
	char	**var;
	int		i;
	int		j;
	int		len_env;
	int		len_exp;

	i = 0;
	j = 0;
	var = NULL;
	len_env = size_vetor(te()->envp);
	len_exp = size_vetor(te()->var_exp);
	var = malloc(sizeof(char *) * (len_env + len_exp + 1));
	if (!var)
		return (set_err(errno), cons_err("export"), FALSE);
	while (te()->envp && te()->envp[j])
		var[i++] = te()->envp[j++];
	j = 0;
	while (te()->var_exp && te()->var_exp[j])
		var[i++] = te()->var_exp[j++];
	var[i] = NULL;
	if (!print_export(var))
		return (cons_err("export"), free(var), FALSE);
	free(var);
	return (TRUE);
}
