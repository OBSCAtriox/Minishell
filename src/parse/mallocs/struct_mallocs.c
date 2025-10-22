#include "../../../includes/minishell.h"

int	malloc_struct(void)
{
	ms()->cmdv = malloc(sizeof(t_pipeline) * ps()->n_cmd + 1);
	if (!ms()->cmdv)
		return (0);
	return (1);
}
