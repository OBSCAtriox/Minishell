#include "../../../includes/minishell.h"

t_parse	*ps(void)
{
	static t_parse	ps;

	return (&ps);
}

void	init_token(int *i, int *buf_i, bool *d_q, bool *s_q)
{
	*i = 0;
	*buf_i = 0;
	*d_q = false;
	*s_q = false;
}
