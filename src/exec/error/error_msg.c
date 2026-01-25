/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:18:37 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/20 18:39:15 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_error(char *comand, char *msg)
{
	if (comand)
	{
		write(2, comand, ft_strlen(comand));
		write(2, ": ", 2);
	}
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}

void	error_cd(char *arg)
{
	write(2, "cd: ", 4);
	perror(arg);
}
