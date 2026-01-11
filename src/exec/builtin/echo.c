/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:17:30 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/11 20:17:31 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_echo(char **argv)
{
	int	n_flag;
	int	printed;
	int	i;

	n_flag = 0;
	printed = 0;
	if (!argv)
	{
		write(1, "\n", 1);
		return (te()->exit_code = 0, FALSE);
	}
	i = 1;
	if (argv[i] && has_new_line(argv[i]))
		n_flag = 1;
	while (argv[i])
	{
		print_echo(argv, i, printed);
		if (!has_new_line(argv[i]))
			printed = 1;
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (te()->exit_code = 0, TRUE);
}

int	has_new_line(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		i += 2;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

void	print_echo(char **argv, int i, int printed)
{
	if (!has_new_line(argv[i]) || printed)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
	}
}
