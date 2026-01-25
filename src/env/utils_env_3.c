/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:35:14 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/18 04:17:01 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_new_local_var(char *name, char *value)
{
	t_data	dt;

	dt.size = size_vetor(te()->l_var);
	dt.env = malloc(sizeof(char *) * (dt.size + 2));
	if (!dt.env)
		return (set_err(errno), FALSE);
	dt.i = 0;
	while (dt.i < dt.size)
	{
		dt.env[dt.i] = ft_strdup(te()->l_var[dt.i]);
		if (!dt.env[dt.i])
			return (free_vetor_failed(&dt.env, dt.i), FALSE);
		dt.i++;
	}
	dt.env[dt.size] = join3(name, EQUAL, value);
	if (!dt.env[dt.size])
		return (free_doble_pointer(dt.env), FALSE);
	dt.env[dt.size + 1] = NULL;
	free_doble_pointer(te()->l_var);
	if (!re_mount_locar_var(dt.env))
		return (free_doble_pointer((dt.env)), FALSE);
	free_doble_pointer(dt.env);
	return (TRUE);
}

int	re_mount_locar_var(char **envp)
{
	int	size;
	int	i;

	i = 0;
	size = size_vetor(envp);
	te()->l_var = malloc(sizeof(char *) * (size + 1));
	if (!te()->l_var)
		return (set_err(errno), FALSE);
	while (envp[i])
	{
		te()->l_var[i] = ft_strdup(envp[i]);
		if (!te()->l_var[i])
		{
			free_vetor_failed(&te()->l_var, i);
			return (FALSE);
		}
		i++;
	}
	te()->l_var[i] = NULL;
	return (TRUE);
}

int	inits_min_var(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("pwd"), FALSE);
	if (!env_set("PWD", pwd, te()->envp))
	{
		free(pwd);
		return (FALSE);
	}
	free(pwd);
	return (TRUE);
}

int	inits_var_exp(t_data *dt)
{
	(*dt).size = size_vetor(te()->var_exp);
	(*dt).env = malloc(sizeof(char *) * ((*dt).size + 1));
	if (!(*dt).env)
		return (set_err(errno), FALSE);
	(*dt).i = 0;
	(*dt).j = 0;
	return (TRUE);
}

int	copy_envp(char **envp)
{
	int	size;
	int	i;

	i = 0;
	if (!*envp)
	{
		if (!inits_min_var())
			return (FALSE);
		return (TRUE);
	}
	size = size_vetor(envp);
	te()->envp = malloc(sizeof(char *) * (size + 1));
	if (!te()->envp)
		return (FALSE);
	while (envp[i])
	{
		te()->envp[i] = ft_strdup(envp[i]);
		if (!te()->envp[i])
			return (free_vetor_failed(&te()->envp, i), FALSE);
		i++;
	}
	te()->envp[i] = NULL;
	return (TRUE);
}
