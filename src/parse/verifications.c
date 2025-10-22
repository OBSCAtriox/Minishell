#include "../../includes/minishell.h"

bool	quotes(const char *line)
{
	int		i;
	bool	d_quote;
	bool	s_quote;

	d_quote = false;
	s_quote = false;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (line[i] == '"' && !s_quote)
			d_quote = !d_quote;
		i++;
	}
	return (!s_quote && !d_quote);
}

int	verifications(const char *line)
{
	num_pipes(line);
	if (!pipe_ver_end(line) || !pipe_ver_start(line) || !pipe_ver_mid(line))
	{
		ps_error(SYNT_ERR);
		return (0);
	}
	quotes(line);
	malloc_struct();
	return (1);
}

void	verific_help(const char *line)
{
	if (quotes(line) || !malloc_struct())
		free_all(ERR_ARG);
}
