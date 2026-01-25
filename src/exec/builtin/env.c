/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:17:33 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/17 19:56:53 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_env(void)
{
	int		i;
	int		size;
	char	*name;
	char	*value;

	i = 0;
	size = size_vetor(te()->envp);
	while (i < size)
	{
		name = get_name_var(te()->envp[i]);
		value = get_value_var(te()->envp[i]);
		if (value)
		{
			write(1, name, ft_strlen(name));
			write(1, "=", 1);
			write(1, value, ft_strlen(value));
			write(1, "\n", 1);
		}
		else
			return (cons_err("env"), free(name), free(value), FALSE);
		free(name);
		free(value);
		i++;
	}
	return (te()->exit_code = 0, TRUE);
}
