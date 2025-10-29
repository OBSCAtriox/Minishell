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

int	main(int argc, char **argv, char **envp)
{
	char		*line;

	(void)argv;
	if (argc != 1)
		basic_error(ERR_ARG);
	mount_envp(envp);
	while (1)
	{
		line = readline("T_Shell>");
		//add_history(line);
		verifications(line);
		if (!ps()->tok)
			printf("list NULL\n");
        for (t_tokens *tmp = ps()->tok; tmp; tmp = tmp->next)
			printf("Value: %s, type: %d\n", tmp->value, tmp->type);
		free(line);
		free_all("Cleaning after command\n");
	}
}
