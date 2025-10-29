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
	if (!quotes(line))
		return (free_all(UNCLOSED_QUOTES), 0);
	if (!pipe_ver_end(line) || !pipe_ver_start(line) || !pipe_ver_mid(line))
		return (ps_error(SYNT_ERR_P), 0);
	if (!r_ver(line))
		return (0);
	num_pipes(line);
	token_list(line);
	malloc_struct();
	return (1);
}
