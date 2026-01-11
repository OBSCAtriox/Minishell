/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:17:42 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/11 20:17:43 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = join3(te()->cwd, NULL, NULL);
		if (!pwd)
		{
			te()->exit_code = 1;
			perror("pwd");
			return (FALSE);
		}
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	te()->exit_code = 0;
	return (TRUE);
}
