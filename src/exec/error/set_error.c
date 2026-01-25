/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 04:59:14 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/18 04:59:15 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_err(int err)
{
	if (tc()->last_err == ENOMEM)
		return ;
	if (tc()->last_err == 0)
		tc()->last_err = err;
}

void	cons_err(char *command)
{
	char	*str_err;

	if (!command || tc()->err_printed)
		return ;
	str_err = NULL;
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	if (tc()->last_err != 0)
	{
		str_err = strerror(tc()->last_err);
		if (!str_err)
			return ;
		write(2, str_err, ft_strlen(str_err));
		write(2, "\n", 1);
	}
	else
		write(2, "failed\n", 7);
	tc()->last_err = 0;
	tc()->err_printed = 1;
}
