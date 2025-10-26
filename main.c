#include "includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>

#define TEST_DIR ".minishell_tests"
#define TEST_OUT_FILE TEST_DIR "/out.txt"
#define TEST_NO_PERM_FILE TEST_DIR "/no_perm.txt"

static char	g_initial_cwd[PATH_MAX];

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

static t_cmd	**create_cmd_vector(size_t count)
{
	t_cmd	**cmdv;

	cmdv = ft_calloc(count + 1, sizeof(t_cmd *));
	if (!cmdv)
		perror("calloc");
	return (cmdv);
}

static int	setup_builtin_pwd(void)
{
	static const char	*args[] = {"pwd", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	cmdv[0]->is_builtin = 1;
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	allocate_redir_slots(t_cmd *cmd, size_t count)
{
	t_redir	**slots;

	if (!cmd)
		return (FALSE);
	if (cmd->redir)
	{
		free(cmd->redir);
		cmd->redir = NULL;
	}
	slots = ft_calloc(count + 1, sizeof(t_redir *));
	if (!slots)
	{
		perror("calloc");
		return (FALSE);
	}
	cmd->redir = slots;
	return (TRUE);
}

static t_redir	*create_redir(t_redir_type type, int fd_target,
				const char *path, int quoted)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (perror("calloc"), NULL);
	redir->type = type;
	redir->fd_target = fd_target;
	redir->hdoc_fd = -1;
	redir->quoted = quoted;
	if (path)
	{
		redir->path = ft_strdup(path);
		if (!redir->path)
		{
			perror("strdup");
			free(redir);
			return (NULL);
		}
	}
	return (redir);
}

static int	redirect_stdin_with_feed(const char *feed, int *saved_stdin)
{
	int		pipefd[2];
	size_t	len;

	if (!feed || !saved_stdin)
		return (FALSE);
	if (pipe(pipefd) < 0)
		return (perror("pipe"), FALSE);
	len = ft_strlen(feed);
	if (len > 0 && write(pipefd[1], feed, len) < 0)
	{
		perror("write");
		close_all(pipefd[0], pipefd[1], -1, -1);
		return (FALSE);
	}
	close(pipefd[1]);
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin < 0)
	{
		perror("dup");
		close(pipefd[0]);
		return (FALSE);
	}
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(pipefd[0]);
		close(*saved_stdin);
		*saved_stdin = -1;
		return (FALSE);
	}
	close(pipefd[0]);
	return (TRUE);
}

static void	restore_stdin(int saved_stdin)
{
	if (saved_stdin < 0)
		return ;
	if (dup2(saved_stdin, STDIN_FILENO) < 0)
		perror("dup2");
	close(saved_stdin);
}

typedef struct s_test_case
{
	const char	*name;
	int			(*setup)(void);
	void		(*post)(void);
	const char	*stdin_feed;
	void		(*runner)(const struct s_test_case *test);
}				t_test_case;

static void	run_test_case(const t_test_case *test)
{
	int	redirected;
	int	saved_stdin;
	int	setup_ok;

	printf("\n== %s ==\n", test->name);
	fflush(stdout);
	redirected = FALSE;
	saved_stdin = -1;
	if (test->stdin_feed)
	{
		if (!redirect_stdin_with_feed(test->stdin_feed, &saved_stdin))
		{
			printf("stdin setup failed, skipping test\n");
			return ;
		}
		redirected = TRUE;
	}
	setup_ok = test->setup();
	if (setup_ok)
	{
		execution();
		printf("Exit_code: %d\n", te()->exit_code);
		if (test->post)
			test->post();
	}
	else
		printf("Test setup failed\n");
	if (redirected)
		restore_stdin(saved_stdin);
	cleanup_test_pipeline();
}

static void	execute_test_case(const t_test_case *test)
{
	if (test->runner)
		test->runner(test);
	else
		run_test_case(test);
}

static void	cleanup_redirection_output(void)
{
	unlink(TEST_OUT_FILE);
}

static void	cleanup_permission_fixture(void)
{
	chmod(TEST_NO_PERM_FILE, 0600);
	unlink(TEST_NO_PERM_FILE);
}

static int	ensure_test_dir(void)
{
	if (mkdir(TEST_DIR, 0700) < 0 && errno != EEXIST)
	{
		perror(TEST_DIR);
		return (FALSE);
	}
	return (TRUE);
}

static void	remove_test_dir(void)
{
	if (rmdir(TEST_DIR) < 0 && errno != ENOENT)
		perror(TEST_DIR);
}

static int	setup_builtin_echo(void)
{
	static const char	*args[] = {"echo", "builtin ok", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	cmdv[0]->is_builtin = 1;
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_external_ls(void)
{
	static const char	*args[] = {"ls", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_pipeline_cat_grep(void)
{
	static const char	*cat_args[] = {"cat", "a.txt", NULL};
	static const char	*grep_args[] = {"grep", "azul", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(2);
	if (!cmdv)
		return (FALSE);
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
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_redirection_roundtrip(void)
{
	static const char	*args[] = {"cat", NULL};
	t_cmd				**cmdv;

	unlink(TEST_OUT_FILE);
	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	if (!allocate_redir_slots(cmdv[0], 2))
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	cmdv[0]->redir[0] = create_redir(R_IN, STDIN_FILENO, "a.txt", 0);
	if (!cmdv[0]->redir[0])
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	cmdv[0]->redir[1] = create_redir(R_OUT, STDOUT_FILENO, TEST_OUT_FILE, 0);
	if (!cmdv[0]->redir[1])
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_command_not_found(void)
{
	static const char	*args[] = {"command_does_not_exist", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_exit_code_probe(void)
{
	static const char	*args[] = {"sh", "-c", "exit 42", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_heredoc_test(void)
{
	static const char	*args[] = {"cat", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	if (!allocate_redir_slots(cmdv[0], 1))
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	cmdv[0]->redir[0] = create_redir(R_HDOC, STDIN_FILENO, "EOF", 0);
	if (!cmdv[0]->redir[0])
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_missing_file_redir(void)
{
	static const char	*args[] = {"cat", NULL};
	const char			*path = "./missing_input.txt";
	t_cmd				**cmdv;

	unlink(path);
	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	if (!allocate_redir_slots(cmdv[0], 1))
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	cmdv[0]->redir[0] = create_redir(R_IN, STDIN_FILENO, path, 0);
	if (!cmdv[0]->redir[0])
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_permission_denied_redir(void)
{
	static const char	*args[] = {"cat", NULL};
	t_cmd				**cmdv;
	int					fd;

	unlink(TEST_NO_PERM_FILE);
	fd = open(TEST_NO_PERM_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (perror(TEST_NO_PERM_FILE), FALSE);
	close(fd);
	if (chmod(TEST_NO_PERM_FILE, 0000) < 0)
	{
		perror("chmod");
		unlink(TEST_NO_PERM_FILE);
		return (FALSE);
	}
	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (cleanup_permission_fixture(), FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
	{
		cleanup_permission_fixture();
		free(cmdv);
		return (FALSE);
	}
	if (!allocate_redir_slots(cmdv[0], 1))
	{
		cleanup_permission_fixture();
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	cmdv[0]->redir[0] = create_redir(R_IN, STDIN_FILENO, TEST_NO_PERM_FILE, 0);
	if (!cmdv[0]->redir[0])
	{
		cleanup_permission_fixture();
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_cd_into_test_dir(void)
{
	static const char	*args[] = {"cd", TEST_DIR, NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	cmdv[0]->is_builtin = 1;
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_builtin_pipeline(void)
{
	static const char	*echo_args[] = {"echo", "builtin pipeline", NULL};
	static const char	*tr_args[] = {"tr", "a-z", "A-Z", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(2);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(echo_args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	cmdv[0]->is_builtin = 1;
	cmdv[1] = create_simple_cmd(tr_args);
	if (!cmdv[1])
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	tp()->cmdv = cmdv;
	return (TRUE);
}

static int	setup_heredoc_signal(void)
{
	static const char	*args[] = {"cat", NULL};
	t_cmd				**cmdv;

	cmdv = create_cmd_vector(1);
	if (!cmdv)
		return (FALSE);
	cmdv[0] = create_simple_cmd(args);
	if (!cmdv[0])
		return (free(cmdv), FALSE);
	if (!allocate_redir_slots(cmdv[0], 1))
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	cmdv[0]->redir[0] = create_redir(R_HDOC, STDIN_FILENO, "SIGINT_STOP", 0);
	if (!cmdv[0]->redir[0])
	{
		free_cmd(cmdv[0]);
		free(cmdv);
		return (FALSE);
	}
	tp()->cmdv = cmdv;
	return (TRUE);
}

static void	run_cd_pwd_case(const t_test_case *test)
{
	char	cwd[PATH_MAX];

	printf("\n== %s ==\n", test->name);
	fflush(stdout);
	if (!test->setup())
	{
		printf("Test setup failed\n");
		return ;
	}
	execution();
	printf("Exit_code (cd): %d\n", te()->exit_code);
	if (test->post)
		test->post();
	cleanup_test_pipeline();
	if (getcwd(cwd, sizeof(cwd)))
		printf("cwd atual: %s\n", cwd);
	else
		perror("getcwd");
	if (setup_builtin_pwd())
	{
		execution();
		printf("Exit_code (pwd): %d\n", te()->exit_code);
		cleanup_test_pipeline();
	}
	else
		printf("pwd setup failed\n");
	if (chdir(g_initial_cwd) < 0)
		perror("chdir");
}

static void	run_heredoc_signal_case(const t_test_case *test)
{
	pid_t	sender;
	int		pipefd[2];
	int		saved_stdin;
	int		setup_ok;

	printf("\n== %s ==\n", test->name);
	fflush(stdout);
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return ;
	}
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
	{
		perror("dup");
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(pipefd[0]);
		close(pipefd[1]);
		restore_stdin(saved_stdin);
		return ;
	}
	close(pipefd[0]);
	setup_ok = test->setup();
	if (!setup_ok)
	{
		printf("Test setup failed\n");
		close(pipefd[1]);
		restore_stdin(saved_stdin);
		return ;
	}
	sender = fork();
	if (sender == 0)
	{
		int	attempt;

		signal(SIGINT, SIG_IGN);
		attempt = 0;
		while (attempt < 10)
		{
			usleep(100000);
			if (kill(0, SIGINT) == 0)
				break ;
			attempt++;
		}
		close(pipefd[1]);
		_exit(EXIT_SUCCESS);
	}
	else if (sender < 0)
		perror("fork");
	close(pipefd[1]);
	execution();
	printf("Exit_code: %d\n", te()->exit_code);
	if (test->post)
		test->post();
	cleanup_test_pipeline();
	if (sender > 0)
		waitpid(sender, NULL, 0);
	restore_stdin(saved_stdin);
}

static const t_test_case	g_tests[] = {
{"Builtin command", setup_builtin_echo, NULL, NULL, NULL},
{"External command", setup_external_ls, NULL, NULL, NULL},
{"Pipeline", setup_pipeline_cat_grep, NULL, NULL, NULL},
{"Pipeline builtin", setup_builtin_pipeline, NULL, NULL, NULL},
{"Redirections", setup_redirection_roundtrip, cleanup_redirection_output, NULL, NULL},
{"Error handling", setup_command_not_found, NULL, NULL, NULL},
{"Exit codes", setup_exit_code_probe, NULL, NULL, NULL},
{"Builtin cd/pwd", setup_cd_into_test_dir, NULL, NULL, run_cd_pwd_case},
{"Heredoc", setup_heredoc_test, NULL, "line via heredoc $USER\nEOF\n", NULL},
{"Heredoc interrupt", setup_heredoc_signal, NULL, NULL, run_heredoc_signal_case},
{"Missing file", setup_missing_file_redir, NULL, NULL, NULL},
{"Permission denied", setup_permission_denied_redir, cleanup_permission_fixture, NULL, NULL}
};

int	main(int argc, char **argv, char **envp)
{
	size_t	i;
	size_t	count;

	(void)argc;
	(void)argv;
	if (!mount_envp(envp))
		return (EXIT_FAILURE);
	if (!ensure_test_dir())
		return (EXIT_FAILURE);
	if (!getcwd(g_initial_cwd, sizeof(g_initial_cwd)))
		return (perror("getcwd"), EXIT_FAILURE);
	if (setpgid(0, 0) < 0)
		perror("setpgid");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	count = sizeof(g_tests) / sizeof(g_tests[0]);
	i = 0;
	while (i < count)
		execute_test_case(&g_tests[i++]);
	remove_test_dir();
	free_all();
	return (0);
}
