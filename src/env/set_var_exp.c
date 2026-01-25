/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:34:55 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/18 04:16:44 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_var_exp(char *name)
{
	if (!te()->var_exp)
	{
		te()->var_exp = malloc(sizeof(char *) * 2);
		if (!te()->var_exp)
			return (set_err(errno));
		te()->var_exp[0] = name;
		te()->var_exp[1] = NULL;
	}
}

int	create_new_var_exp(char *name)
{
	t_data	dt;

	dt.size = size_vetor(te()->var_exp);
	dt.env = malloc(sizeof(char *) * (dt.size + 2));
	if (!dt.env)
		return (set_err(errno), FALSE);
	dt.i = 0;
	while (dt.i < dt.size)
	{
		dt.env[dt.i] = ft_strdup(te()->var_exp[dt.i]);
		if (!dt.env[dt.i])
			return (set_err(errno), free_vetor_failed(&dt.env, dt.i), FALSE);
		dt.i++;
	}
	dt.env[dt.size] = join3(name, NULL, NULL);
	if (!dt.env[dt.size])
		return (free_doble_pointer(dt.env), FALSE);
	dt.env[dt.size + 1] = NULL;
	if (!re_mount_var_exp(dt.env))
		return (free_doble_pointer((dt.env)), FALSE);
	free_doble_pointer(dt.env);
	return (TRUE);
}

int	re_mount_var_exp(char **envp)
{
	int	size;
	int	i;

	i = 0;
	size = size_vetor(envp);
	if (te()->var_exp)
	{
		free_doble_pointer(te()->var_exp);
		te()->var_exp = NULL;
	}
	te()->var_exp = malloc(sizeof(char *) * (size + 1));
	if (!te()->var_exp)
		return (set_err(errno), FALSE);
	while (envp[i])
	{
		te()->var_exp[i] = ft_strdup(envp[i]);
		if (!te()->var_exp[i])
		{
			free_vetor_failed(&te()->var_exp, i);
			return (FALSE);
		}
		i++;
	}
	te()->var_exp[i] = NULL;
	return (TRUE);
}

int	update_var_exp(char *name)
{
	int	index;

	index = find_variable(name, te()->envp);
	if (index != -1)
		return (TRUE);
	index = find_variable(name, te()->var_exp);
	if (index != -1)
		return (TRUE);
	if (!te()->var_exp)
	{
		if (!create_new_var_exp(name))
			return (FALSE);
	}
	else
	{
		if (!create_new_var_exp(name))
			return (FALSE);
	}
	return (TRUE);
}

int	remove_var_exp(int index)
{
	t_data	dt;

	if (index == -1 || !te()->var_exp)
		return (TRUE);
	if (!inits_var_exp(&dt))
		return (FALSE);
	while (te()->var_exp[dt.i])
	{
		if (skip_var_dell(index, &dt.i))
			continue ;
		dt.env[dt.j] = ft_strdup(te()->var_exp[dt.i]);
		if (!dt.env[dt.j])
			return (set_err(errno), free_vetor_failed(&dt.env, dt.j), FALSE);
		dt.i++;
		dt.j++;
	}
	dt.env[dt.j] = NULL;
	if (!re_mount_var_exp(dt.env))
		return (free_doble_pointer(dt.env), FALSE);
	free_doble_pointer(dt.env);
	return (TRUE);
}
