#include "../../../includes/minishell.h"

void	buf_i_ver(t_tokens **head, t_tokens **tail, char *buf, int *buf_i, bool yn)
{
	if (*buf_i > 0)
		create_token(head, tail, buf, *buf_i);
	if (yn)
		*buf_i = 0;
}

void	quotes_ver(bool *d_quotes, bool *s_quotes, char c)
{
	if (c == '\'' && !*d_quotes)
		*s_quotes = !*s_quotes;
	else if (c == '"' && !*s_quotes)
		*d_quotes = !*d_quotes;
}

void	inc_i(int *i, int n)
{
	if (n == 1)
		(*i) += 2;
	else
		(*i)++;
}
