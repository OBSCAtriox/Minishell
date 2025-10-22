#include "../../../includes/minishell.h"

t_parse	*ps(void)
{
	static t_parse	ps;

	return (&ps);
}
