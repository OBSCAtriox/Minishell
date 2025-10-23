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
	t_tokens	*list;
	char		*line;

    list = NULL;
	(void)argv;
	if (argc != 1)
		basic_error(ERR_ARG);
	mount_envp(envp);
	while (1)
	{
		line = readline("T_Shell>");
		add_history(line);
		verifications(line);
        list = token_list(line);
		if (!list)
			printf("list NULL\n");
        for (t_tokens *tmp = list; tmp; tmp = tmp->next)
			printf("Value: %s, type: %d\n", tmp->value, tmp->type);
		free(line);
	}
}
