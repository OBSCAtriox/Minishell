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
	initis_main(argc, argv, envp);
	while (1)
	{
		tc()->g_sig = 0;
		setup_prompt_signal();
		if(!readline_and_check())
			break;
		if(check_sigint())
			continue;
		if(empty_line())
			continue;
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
	exit_main();
}
