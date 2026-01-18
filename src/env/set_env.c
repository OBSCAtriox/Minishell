/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:34:40 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/18 04:16:10 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mount_envp(char **envp)
{
	int	size;
	int	i;

	i = 0;
	size = size_vetor(envp);
	te()->envp = malloc(sizeof(char *) * (size + 1));
	if (!te()->envp)
		return (set_err(errno), FALSE);
	while (envp[i])
	{
		te()->envp[i] = ft_strdup(envp[i]);
		if (!te()->envp[i])
		{
			set_err(errno);
			free_vetor_failed(&te()->envp, i);
			return (FALSE);
		}
		i++;
	}
	te()->envp[i] = NULL;
	return (TRUE);
}

int	update_variable(char *name, char *value, char **env)
{
	t_data	dt;
	int		i;

	dt.size = size_vetor(env);
	dt.env = malloc(sizeof(char *) * (dt.size + 2));
	if (!dt.env)
		return (set_err(errno), FALSE);
	i = 0;
	while (i < dt.size)
	{
		dt.env[i] = ft_strdup(env[i]);
		if (!dt.env[i])
			return (free_vetor_failed(&dt.env, i), FALSE);
		i++;
	}
	dt.env[dt.size] = join3(name, EQUAL, value);
	if (!dt.env[dt.size])
		return (free_vetor_failed(&dt.env, i), FALSE);
	dt.env[dt.size + 1] = NULL;
	free_doble_pointer(env);
	if (!mount_envp(dt.env))
		return (free_doble_pointer(dt.env), FALSE);
	free_doble_pointer(dt.env);
	return (TRUE);
}

int	env_set(char *name, char *value, char **env)
{
	t_data	dt;
	char	*tmp;

	dt.index = find_variable(name, env);
	dt.size = size_vetor(env);
	if (dt.index != -1)
	{
		tmp = env[dt.index];
		env[dt.index] = join3(name, EQUAL, value);
		if (!env[dt.index])
		{
			env[dt.index] = tmp;
			return (FALSE);
		}
		free(tmp);
	}
	else if (dt.index == -1)
	{
		if (!update_variable(name, value, env))
			return (FALSE);
	}
	return (TRUE);
}

void	update_local_var(char *name, char *value)
{
	int		index;
	char	**l_var;
	char	*new;

	if (!te()->l_var)
	{
		create_local_variable(name, value);
		return ;
	}
	l_var = te()->l_var;
	index = find_variable(name, l_var);
	if (index != -1)
	{
		new = join3(name, EQUAL, value);
		if (!new)
			return (print_error(NULL, "error creating local variable"));
		free(l_var[index]);
		l_var[index] = new;
	}
	else
	{
		if (!create_new_local_var(name, value))
			return (print_error(NULL, "error creating local variable"));
	}
}
