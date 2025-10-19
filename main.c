#include "includes/minishell.h"
#include <stdio.h>

t_pipeline *tp(void)
{
	static t_pipeline pipe;

	return (&pipe);
}

t_env	*te(void)
{
	static t_env	env;

	return (&env);
}

static void	*xfail_malloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = calloc(count, size);
	if (!ptr)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

static t_redir	*create_heredoc_redir(const char *delimiter, int quoted)
{
	t_redir	*redir;

	redir = xfail_malloc(1, sizeof(*redir));
	redir->type = R_HDOC;
	redir->fd_target = STDIN_FILENO;
	redir->path = ft_strdup(delimiter);
	if (!redir->path)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	redir->hdoc_fd = -1;
	redir->quoted = quoted;
	return (redir);
}

static void	setup_test_pipeline(void)
{
	t_cmd	**cmdv;
	t_cmd	*cmd;
	t_redir	**redir;

	cmdv = xfail_malloc(2, sizeof(*cmdv));
	cmd = xfail_malloc(1, sizeof(*cmd));
	redir = xfail_malloc(3, sizeof(*redir));
	redir[0] = create_heredoc_redir("EOF", 0);
	redir[1] = create_heredoc_redir("EOF_QUOTED", 1);
	redir[2] = NULL;
	cmd->argv = NULL;
	cmd->redir = redir;
	cmd->is_builtin = 0;
	cmdv[0] = cmd;
	cmdv[1] = NULL;
	tp()->cmdv = cmdv;
}

static void	print_heredoc_result(t_redir *redir)
{
	ssize_t	bytes;
	char	buffer[256];

	if (!redir)
		return ;
	if (redir->hdoc_fd < 0)
	{
		printf("heredoc() finalizado, mas hdoc_fd nao foi definido.\n");
		return ;
	}
	printf("\nConteudo armazenado no heredoc (%s%s):\n",
		redir->quoted ? "quoted " : "",
		redir->path);
	while ((bytes = read(redir->hdoc_fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes] = '\0';
		printf("%s", buffer);
	}
	if (bytes < 0)
		perror("read");
	close(redir->hdoc_fd);
	redir->hdoc_fd = -1;
}

static void	cleanup_pipeline(void)
{
	int		i;
	int		j;
	t_cmd	**cmdv;

	cmdv = tp()->cmdv;
	if (!cmdv)
		return ;
	i = 0;
	while (cmdv[i])
	{
		if (cmdv[i]->redir)
		{
			j = 0;
			while (cmdv[i]->redir[j])
			{
				if (cmdv[i]->redir[j]->hdoc_fd >= 0)
					close(cmdv[i]->redir[j]->hdoc_fd);
				free(cmdv[i]->redir[j]->path);
				free(cmdv[i]->redir[j]);
				j++;
			}
			free(cmdv[i]->redir);
		}
		free(cmdv[i]);
		i++;
	}
	free(cmdv);
	tp()->cmdv = NULL;
}

static void	cleanup_env(void)
{
	if (te()->envp)
	{
		free_doble_pointer(te()->envp);
		te()->envp = NULL;
	}
}

static void	cleanup(void)
{
	cleanup_pipeline();
	cleanup_env();
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	parent_pid;

	signal(SIGQUIT, SIG_IGN);
	mount_envp(envp);
	te()->exit_code = 0;
	(void)argc;
	(void)argv;
	setup_test_pipeline();
	printf("Teste de heredoc():\n");
	printf("- primeiro heredoc (EOF) sem aspas, expansoes ativas.\n");
	printf("- segundo heredoc (EOF_QUOTED) com aspas simuladas, sem expansoes.\n");
	printf("Finalize cada entrada digitando o delimitador correspondente.\n");
	fflush(stdout);
	parent_pid = getpid();
	heredoc();
	if (getpid() != parent_pid)
		_exit(EXIT_SUCCESS);
	print_heredoc_result(tp()->cmdv[0]->redir[0]);
	print_heredoc_result(tp()->cmdv[0]->redir[1]);
	cleanup();
	return (0);
}
