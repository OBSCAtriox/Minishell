#include "../../includes/minishell.h"

static int verify_whitespaces(const char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ms_isspaces(line[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

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
	if (!line || !*line)
		return (0);
	if (!verify_whitespaces(line))
		return (0);
	if (!quotes(line))
		return (free_all(UNCLOSED_QUOTES, 0), 0);
	if (!pipe_ver_end(line) || !pipe_ver_start(line) || !pipe_ver_mid(line))
		return (ps_error(SYNT_ERR_P), 0);
	if (!r_ver(line))
		return (0);
	num_pipes(line);
	token_list(line);
	ver_to_expand(ps()->tok);
	malloc_struct();
	verifications_after_malloc_struct(ps()->tok);
	return (1);
}
