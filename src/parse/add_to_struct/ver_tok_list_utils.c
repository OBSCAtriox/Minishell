#include "../../../includes/minishell.h"

static int	ver_if_builtin(const char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") 
		|| !ft_strcmp(cmd,"pwd") || !ft_strcmp(cmd, "unset") 
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "env") 
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

void	redir_arr_malloc(int size, int i)
{
	ms()->cmdv[i]->redir = malloc(sizeof(t_redir) * size);
	if (!ms()->cmdv[i]->redir)
		free_all(MALLOC_FAIL, 1);
}

static void	malloc_ms_argv(t_tokens *t, int cmd_i)
{
	int	count;

	count = 0;
	while (t)
	{
		if (t->type == WORD)
			count++;
		t = t->next;
	}
	ms()->cmdv[cmd_i]->argv = malloc(sizeof(char *) * (count + 1));
	if (!ms()->cmdv[cmd_i]->argv)
		free_all(MALLOC_FAIL, 1);
}

static void	add_cmd_to_argv(t_tokens *t, int cmd_i)
{
	int	i;

	i = 0;
	if (t->type == WORD)
	{
		ms()->cmdv[cmd_i]->argv[i++] = ft_strdup(t->value);
		t = t->next;
	}
	while (t)
	{
		if (t->type == WORD && !if_redir(t->prev->type))
		{
			ms()->cmdv[cmd_i]->argv[i] = ft_strdup(t->value);
			if (!ms()->cmdv[cmd_i]->argv[i])
				free_all(MALLOC_FAIL, 1);
			i++;
		}
		t = t->next;
	}
	ms()->cmdv[cmd_i]->argv[i] = NULL;
	ms()->cmdv[cmd_i]->is_builtin = ver_if_builtin(ms()->cmdv[cmd_i]->argv[0]);
}

void	add_cmd_argv(t_per_cmd_tok *tl)
{
	int	i;

	i = 0;
	while (ms()->cmdv[i])
	{
		malloc_ms_argv(tl->cmdt, i);
		add_cmd_to_argv(tl->cmdt, i);
		tl = tl->next;
		i++;
	}
}
