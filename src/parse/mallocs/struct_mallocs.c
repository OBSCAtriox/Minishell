#include "../../../includes/minishell.h"

int	malloc_struct(void)
{
	int i;

	i = 0;
	ms()->cmdv = ft_calloc(ps()->n_cmd + 1, sizeof(t_cmd *));
	if (!ms()->cmdv)
		free_all(MALLOC_FAIL, 1);
	while (i < ps()->n_cmd)
	{
		ms()->cmdv[i] = ft_calloc(1, sizeof(t_cmd));
		if (!ms()->cmdv[i])
			free_all(MALLOC_FAIL, 1);
		i++;
	}
	ms()->cmdv[i] = NULL;
	return (1);
}

int malloc_redir_struct(int cmd_i, int size)
{
	int i;

	ms()->cmdv[cmd_i]->redir = ft_calloc(size + 1, sizeof(t_redir *));
	if (!ms()->cmdv[cmd_i]->redir)
		free_all(MALLOC_FAIL, 1);
	i = 0;
	while (i < size)
	{
		ms()->cmdv[cmd_i]->redir[i] = ft_calloc(1, sizeof(t_redir));
		if (!ms()->cmdv[cmd_i]->redir[i])
			free_all(MALLOC_FAIL, 1);
		i++;
	}
	return (1);
}
