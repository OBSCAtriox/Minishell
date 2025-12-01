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

void	init_s_var(t_vars *var)
{
	var->i = 0;
	var->y = 0;
	var->d_q = false;
	var->s_q = false;
}

void	init_split_vars(t_split_var *va)
{
	va->head = NULL;
	va->tail = NULL;
	va->ty = NONE;
	va->i = 0;
	va->st = 0;
}
