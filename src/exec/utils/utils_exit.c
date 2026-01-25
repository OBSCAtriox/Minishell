/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:31:00 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/11 20:31:26 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	define_limits_exit(unsigned long long *limit, int sign)
{
	if (sign)
		*limit = (unsigned long long)LLONG_MAX + 1;
	else
		*limit = (unsigned long long)LLONG_MAX;
}

void	print_exit(void)
{
	if (tc()->in_parent)
		write(1, "exit\n", 5);
}
