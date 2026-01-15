/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:56:26 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/15 16:40:11 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ps_error(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

void	basic_error(char *msg)
{
	if (!ft_strcmp(MALLOC_FAIL, msg))
		te()->exit_code = 1;
	write(1, msg, ft_strlen(msg));
	exit(1);
}
