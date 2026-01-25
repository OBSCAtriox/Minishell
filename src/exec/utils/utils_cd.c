/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:14:43 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/17 23:20:35 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	aux_cd(char *new_pwd, char *old_pwd, char *target)
{
	if (te()->oldpwd)
		free(te()->oldpwd);
	te()->oldpwd = old_pwd;
	free(te()->cwd);
	te()->cwd = ft_strdup(new_pwd);
	if (!te()->cwd)
	{
		free_cd(&new_pwd, &target, &old_pwd, 0);
		return (cons_err("cd"), FALSE);
	}
	if (!env_set("PWD", new_pwd, te()->envp))
	{
		free_cd(&new_pwd, &target, &old_pwd, 0);
		return (cons_err("cd"), FALSE);
	}
	if (!env_set("OLDPWD", old_pwd, te()->envp))
	{
		free_cd(&new_pwd, &target, &old_pwd, 0);
		return (cons_err("cd"), FALSE);
	}
	free_cd(&new_pwd, &target, &old_pwd, 0);
	te()->exit_code = 0;
	return (TRUE);
}

void	print_cd_back(char **arg, char *target)
{
	if (arg[1] && arg[1][0] == '-' && arg[1][1] == '\0')
	{
		write(1, target, ft_strlen(target));
		write(1, "\n", 1);
	}
}
