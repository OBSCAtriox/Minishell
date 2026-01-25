/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:14:16 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/24 23:11:22 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initis_main(int argc, char **argv, char **envp)
{
	(void)argv;
	tc()->g_sig = 0;
	if (argc != 1)
		basic_error(ERR_ARG);
	if (!copy_envp(envp))
	{
		print_error("T_Shell", "initialization failure");
		exit(1);
	}
	if (!shell_level())
	{
		print_error("T_Shell", "initialization failure");
		cleanup();
		exit(1);
	}
	set_cwd();
	tc()->last_err = 0;
}

int	readline_and_check(void)
{
	char	*prompt;

	tc()->err_printed = 0;
	rl_on_new_line();
	prompt = build_prompt();
	if (!prompt)
		ps()->line = readline(RL_GREEN "T_shell " RL_WHITE " -> " RL_RESET);
	else
	{
		ps()->line = readline(prompt);
		free(prompt);
	}
	if (!ps()->line)
	{
		write(1, "exit\n", 5);
		return (FALSE);
	}
	return (TRUE);
}

int	check_sigint(void)
{
	if (tc()->g_sig == SIGINT && ps()->line && ps()->line[0] == '\0')
	{
		tc()->g_sig = 0;
		free(ps()->line);
		return (TRUE);
	}
	tc()->g_sig = 0;
	return (FALSE);
}

int	empty_line(void)
{
	if (ps()->line[0] == '\0')
	{
		free(ps()->line);
		return (TRUE);
	}
	return (FALSE);
}

void	exit_main(void)
{
	rl_clear_history();
	cleanup();
	exit(te()->exit_code);
}
