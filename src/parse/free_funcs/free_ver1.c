#include "../../../includes/minishell.h"

void	free_all(char *msg)
{
	if (ps()->p_pipe)
		free(ps()->p_pipe);
	/* if (ms()->cmdv)
	{
	} */
	ps_error(msg);
}
