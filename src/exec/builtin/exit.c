/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:17:36 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/17 20:25:00 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_valid_arg(char *arg)
{
	if (!arg || arg[0] == '\0')
	{
		print_error("exit", "numeric argument required");
		return (FALSE);
	}
	return (TRUE);
}

static void	check_after_two_arg(char *arg)
{
	if (!check_number(arg))
	{
		if (tc()->in_parent)
		{
			restore_std();
			cleanup();
		}
		else
			cleanup();
		exit(2);
	}
}

static void	more_than_one(char **arg)
{
	print_exit();
	check_after_two_arg(arg[1]);
	print_error("exit", "too many arguments");
	te()->exit_code = 1;
}

int	builtin_exit(char **arg)
{
	long long	code;

	code = 0;
	if (!arg[1])
		code = te()->exit_code;
	else if (arg[2])
		return (more_than_one(arg), FALSE);
	else
	{
		print_exit();
		if (!check_valid_arg(arg[1]) || !check_number(arg[1]))
			code = 2;
		else
			code = ft_atoi(arg[1]) % 256;
	}
	if (tc()->in_parent)
	{
		restore_std();
		cleanup();
	}
	else
		cleanup();
	exit(code);
}

int	check_number(char *arg)
{
	int					sign;
	unsigned long long	result;
	unsigned long long	limit;
	int					i;

	i = 0;
	sign = 0;
	result = 0;
	if ((arg[i] == '-' || arg[i] == '+') && arg[i + 1])
	{
		if (arg[i] == '-')
			sign = 1;
		i++;
	}
	define_limits_exit(&limit, sign);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (print_error("exit", "numeric argument required"), FALSE);
		if (result > (limit - (arg[i] - '0')) / 10)
			return (print_error("exit", "numeric argument required"), FALSE);
		result = result * 10 + (arg[i] - '0');
		i++;
	}
	return (TRUE);
}
