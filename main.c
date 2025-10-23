#include "includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

t_pipeline	*tp(void)
{
	static t_pipeline	pipe;

	return (&pipe);
}

t_env	*te(void)
{
	static t_env	env;

	return (&env);
}

static void	free_cmd(t_cmd *cmd)
{
	int	j;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		j = 0;
		while (cmd->argv[j])
		{
			free(cmd->argv[j]);
			j++;
		}
		free(cmd->argv);
	}
	if (cmd->redir)
	{
		j = 0;
		while (cmd->redir[j])
		{
			if (cmd->redir[j]->path)
				free(cmd->redir[j]->path);
			if (cmd->redir[j]->type == R_HDOC
				&& cmd->redir[j]->hdoc_fd >= 0)
				close(cmd->redir[j]->hdoc_fd);
			free(cmd->redir[j]);
			j++;
		}
		free(cmd->redir);
	}
	free(cmd);
}

static void	cleanup_test_pipeline(void)
{
	t_cmd	**cmdv;
	int		i;

	cmdv = tp()->cmdv;
	if (!cmdv)
		return ;
	i = 0;
	while (cmdv[i])
	{
		free_cmd(cmdv[i]);
		i++;
	}
	free(cmdv);
	tp()->cmdv = NULL;
}

static char	**dup_args(const char *args[])
{
	char	**copy;
	size_t	count;
	size_t	i;

	count = 0;
	while (args[count])
		count++;
	copy = ft_calloc(count + 1, sizeof(char *));
	if (!copy)
		return (perror("calloc"), NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(args[i]);
		if (!copy[i])
		{
			perror("strdup");
			while (i > 0)
			{
				free(copy[i - 1]);
				i--;
			}
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

static t_cmd	*create_simple_cmd(const char *args[])
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (perror("calloc"), NULL);
	cmd->argv = dup_args(args);
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redir = ft_calloc(1, sizeof(t_redir *));
	if (!cmd->redir)
	{
		perror("calloc");
		free_cmd(cmd);
		return (NULL);
	}
	cmd->is_builtin = 0;
	return (cmd);
}

static int	setup_test_pipeline(void)
{
	static const char	*cat_args[] = {"cat", "a.txt", NULL};
	static const char	*grep_args[] = {"grep", "azul", NULL};
	t_cmd				**cmdv;

	cmdv = ft_calloc(3, sizeof(t_cmd *));
	if (!cmdv)
		return (perror("calloc"), FALSE);
	cmdv[0] = create_simple_cmd(cat_args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	cmdv[1] = create_simple_cmd(grep_args);
	if (!cmdv[1])
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	cmdv[2] = NULL;
	tp()->cmdv = cmdv;
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!mount_envp(envp))
		return (EXIT_FAILURE);
	if (!setup_test_pipeline())
	{
		free_all();
		return (EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	execution();
	printf("Exit_code: %d\n", te()->exit_code);
	cleanup_test_pipeline();
	free_all();
	return (0);
}
