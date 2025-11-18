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
	//int i;

	//i = 0;
	(void)argv;
	if (argc != 1)
		basic_error(ERR_ARG);
	mount_envp(envp);
	printf("%s\n", expand_line("Ola $? $9 boas \"$1\""));
	while (1)
	{
		line = readline("T_Shell> ");
		add_history(line);
		verifications(line);
		if (!ps()->tok)
			printf("list NULL\n");
        for (t_tokens *tmp = ps()->tok; tmp; tmp = tmp->next)
			printf("Value: %s, type: %d\n", tmp->value, tmp->type);
		/* while (te()->envp[i])
		{
			write(1, te()->envp[i], ft_strlen(te()->envp[i]));
			write(1, "\n", 1);
			i++;
		} */
		free(line);
		free_all("Cleaning after command\n", 0);
	}
}
