#include "../../includes/minishell.h"

int	mount_envp(char **envp)
{
	int	size;
	int	i;

	i = 0;
	size = size_vetor(envp);
	te()->envp = malloc(sizeof(char *) * (size + 1));
	if (!te()->envp)
		return (FALSE);
	while (envp[i])
	{
		te()->envp[i] = ft_strdup(envp[i]);
		if (!te()->envp[i])
		{
			free_vetor_failed(te()->envp, i);
			return (FALSE);
		}
		i++;
	}
	te()->envp[i] = NULL;
	return (TRUE);
}

int	update_variable(char *name, char *value, char **env)
{
	t_data	dt;
	int		i;

	dt.size = size_vetor(env);
	dt.env = malloc(sizeof(char *) * (dt.size + 2));
	if (!dt.env)
		return (FALSE);
	i = 0;
	while (i < dt.size)
	{
		dt.env[i] = ft_strdup(env[i]);
		if (!dt.env[i])
			return (free_vetor_failed(dt.env, i), FALSE);
		i++;
	}
	dt.env[dt.size] = join3(name, EQUAL, value);
	if (!dt.env[dt.size])
		return (free_vetor_failed(dt.env, i), FALSE);
	dt.env[dt.size + 1] = NULL;
	free_doble_pointer(env);
	if (!mount_envp(dt.env))
		return (free_doble_pointer(dt.env), FALSE);
	free_doble_pointer(dt.env);
	return (TRUE);
}

int	env_set(char *name, char *value, char **env)
{
	t_data	dt;

	dt.index = find_variable(name, env);
	dt.size = size_vetor(env);
	if (dt.index != -1)
	{
		free(env[dt.index]);
		env[dt.index] = join3(name, EQUAL, value);
		return (1);
	}
	else if (dt.index == -1 && dt.size > 0)
	{
		if (!update_variable(name, value, env))
			return (print_error(NULL, "failed to add variable"), 0);
	}
	return (1);
}

void	update_local_var(char *name, char *value)
{
	int	index;

	if (!te()->l_var)
		return ;
	index = find_variable(name, te()->l_var);
	if (index != -1)
	{
		free(te()->l_var[index]);
		te()->l_var[index] = join3(name, EQUAL, value);
	}
	else
	{
		if (!create_new_local_var(name, value))
			return (print_error(NULL, "error creating local variable"));
	}
}
