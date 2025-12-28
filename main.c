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
	tc()->g_sig = 0;
	if (argc != 1)
		basic_error(ERR_ARG);
	mount_envp(envp);
	shell_level();
	set_cwd();
	// printf("%s\n", expand_line("Ola $? $9 boas \"$1\""));
	while (1)
	{
		tc()->g_sig = 0;
		setup_prompt_signal();
		ps()->line = readline("T_Shell> ");
		if (!ps()->line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if(tc()->g_sig == SIGINT)
		{
    		tc()->g_sig = 0;
    		free(ps()->line);
    		continue;
		}
		if (ps()->line[0] == '\0')
		{
			free(ps()->line);
			continue ;
		}
		if (!verify_whitespaces(ps()->line))
			continue ;
		add_history(ps()->line);
		if (!verifications(ps()->line))
		{
			free_all("", 0);
			continue;
		}
		else
			execution();
		free_all("", 0);
		ps()->line = NULL;
	}
	rl_clear_history();
	cleanup();
	exit(te()->exit_code);
}
