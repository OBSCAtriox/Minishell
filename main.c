#include "includes/minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

t_pipeline *tp(void)
{
	static t_pipeline pipe;

	return (&pipe);
}

t_env	*te(void)
{
	static t_env	env;

	return (&env);
}

int	main(int argc, char **argv, char **envp)
{
	int	*index;
	int	*len;
	char	**var;
	int		size;
	char *line;

	mount_envp(envp);
	te()->exit_code = 255;
	(void)argc;
	(void)argv;
	line = "$USER $USER $USERR";
	exp_find_var(line, &index, &len);
	var = exp_str_var(line);
	size = count_len_exp(line);
	for(int i = 0; index[i]; i++)
		printf("index: %d -- len: %d\n", index[i], len[i]);
	for(int i = 0; var[i]; i++)
		printf("var: %s\n", var[i]);
	printf("\n");
	printf("size: %d\n", size);
	return (0);
}
