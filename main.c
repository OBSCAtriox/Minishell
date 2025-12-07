#include "includes/minishell.h"

t_env	*te(void)
{
	static t_env	env;

	return (&env);
}

t_pipeline	*ms(void)
{
	static t_pipeline	ms;

	return (&ms);
}

/* static void	printf_list_tok(t_per_cmd_tok *tl)
{
	t_tokens	*tmp;

	while (tl)
	{
		printf("\n//////////////////////\n");
		tmp = tl->cmdt;
		while (tmp)
		{
			printf("list of tok list : --> %s\n", tmp->value);
			printf("\n------------------\n");
			tmp = tmp->next;
		}
		tl = tl->next;
	}
} */

int	main(int argc, char **argv, char **envp)
{
			//int count;
			//t_per_cmd_tok *tl;
	//t_tokens	*cur;
	//int			y;

	// int i;
	// i = 0;
	(void)argv;
	setup_prompt_signal();
	if (argc != 1)
		basic_error(ERR_ARG);
	mount_envp(envp);
	// printf("%s\n", expand_line("Ola $? $9 boas \"$1\""));
	while (1)
	{
		ps()->line = readline("T_Shell> ");
		if (!ps()->line)
			break ;
		if (ps()->line[0] == '\0')
		{
			free(ps()->line);
			continue ;
		}
		add_history(ps()->line);
		if (!verify_whitespaces(ps()->line))
			continue ;
		if (!verifications(ps()->line))
		{
			free_all("", 0);
			cleanup();
			exit(1);
		}
		else
		{
			//print_minishell_structs(1);
			execution();
		}
		free_all("", 0);
		ps()->line = NULL;
	}
	rl_clear_history();
	cleanup();
}
