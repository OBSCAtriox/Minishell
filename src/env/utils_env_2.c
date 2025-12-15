#include "../../includes/minishell.h"

char	*expand_variable(char *name, char **env)
{
	int		index_variable;
	t_data	dt;
	char	*result;

	index_variable = find_variable(name, env);
	if (index_variable == -1)
		return (NULL);
	dt.temp = env[index_variable];
	dt.len = ft_strlen(dt.temp);
	dt.i = 0;
	dt.j = 0;
	while (dt.temp[dt.i] != '=')
		dt.i++;
	result = malloc(sizeof(char) * ((dt.len - dt.i) + 1));
	if (!result)
		return (NULL);
	dt.i++;
	while (dt.temp[dt.i])
	{
		result[dt.j] = dt.temp[dt.i];
		dt.j++;
		dt.i++;
	}
	result[dt.j] = '\0';
	return (result);
}

void	create_local_variable(char *name, char *value)
{
	if (!te()->l_var)
	{
		te()->l_var = malloc(sizeof(char *) + 2);
		if (!te()->l_var)
			return ;
		te()->l_var[0] = join3(name, EQUAL, value);
		te()->l_var[1] = NULL;
	}
}

char	*get_name_var(char *arg)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = arg[j];
		j++;
	}
	result[i] = '\0';
	return (result);
}

char	*get_value_var(char *arg)
{
	t_data	dt;
	char	*result;

	dt.len = ft_strlen(arg);
	dt.i = 0;
	while (arg[dt.i] && arg[dt.i] != '=')
		dt.i++;
	if (arg[dt.i] != '=')
		return (NULL);
	if (arg[dt.i + 1] == 32 || arg[dt.i + 1] == '\0')
		return (ft_strdup(""));
	result = malloc(sizeof(char) * ((dt.len - dt.i) + 1));
	if (!result)
		return (NULL);
	dt.i++;
	dt.j = 0;
	while (arg[dt.i])
	{
		result[dt.j] = arg[dt.i];
		dt.j++;
		dt.i++;
	}
	result[dt.j] = '\0';
	return (result);
}
