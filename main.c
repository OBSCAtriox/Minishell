#include "includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>

#define TEST_OUTFILE "./execution_builtin_output.txt"

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

static int	str_equals(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	return (ft_strncmp(a, b, ft_strlen(a) + 1) == 0);
}

static const char	*bool_to_label(int success)
{
	return (success ? "sucesso" : "falha");
}

static void	print_vector(const char *label, char **vector)
{
	int	i;

	printf("%s\n", label);
	if (!vector)
	{
		printf("  (null)\n");
		return ;
	}
	i = 0;
	while (vector[i])
	{
		printf("  [%d] %s\n", i, vector[i]);
		i++;
	}
}

static void	init_control_defaults(void)
{
	tc()->num_cmd = 0;
	tc()->num_redr = 0;
	tc()->signaled_heredoc = 0;
	tc()->hdoc_wfd = -1;
	tc()->fd_stdout = -1;
	tc()->fd_stdin = -1;
	te()->exit_code = 0;
}

static t_redir	*create_out_redir(const char *path)
{
	t_redir	*redir;

	redir = xfail_malloc(1, sizeof(*redir));
	redir->type = R_OUT;
	redir->fd_target = STDOUT_FILENO;
	redir->path = ft_strdup(path);
	if (!redir->path)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	redir->hdoc_fd = -1;
	redir->quoted = 0;
	return (redir);
}

static char	**create_builtin_argv(void)
{
	char	**argv;

	argv = xfail_malloc(3, sizeof(*argv));
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("");
	argv[2] = NULL;
	if (!argv[0] || !argv[1])
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	return (argv);
}

static void	setup_execution_test(void)
{
	t_cmd		**cmdv;
	t_cmd		*cmd;
	t_redir		**redir;

	cmdv = xfail_malloc(2, sizeof(*cmdv));
	cmd = xfail_malloc(1, sizeof(*cmd));
	cmd->argv = create_builtin_argv();
	redir = xfail_malloc(2, sizeof(*redir));
	redir[0] = create_out_redir(TEST_OUTFILE);
	redir[1] = NULL;
	cmd->redir = redir;
	cmd->is_builtin = 1;
	cmdv[0] = cmd;
	cmdv[1] = NULL;
	tp()->cmdv = cmdv;
}

static void	print_outfile(void)
{
	int		fd;
	ssize_t	read_bytes;
	char	buffer[256];

	fd = open(TEST_OUTFILE, O_RDONLY);
	if (fd < 0)
	{
		perror(TEST_OUTFILE);
		return ;
	}
	printf("\nConteudo produzido pelo builtin redirecionado para %s:\n", TEST_OUTFILE);
	while ((read_bytes = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[read_bytes] = '\0';
		printf("%s", buffer);
	}
	if (read_bytes < 0)
		perror("read");
	close(fd);
	printf("\n");
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
		if (cmdv[i]->argv)
			free_doble_pointer(cmdv[i]->argv);
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
	if (te()->l_var)
	{
		free_doble_pointer(te()->l_var);
		te()->l_var = NULL;
	}
	if (te()->oldpwd)
	{
		free(te()->oldpwd);
		te()->oldpwd = NULL;
	}
}

static void	cleanup(void)
{
	cleanup_pipeline();
	cleanup_env();
}

static int	run_execution_test(char **envp)
{
	int	saved_stdout;

	cleanup();
	if (!mount_envp(envp))
	{
		fprintf(stderr, "Erro ao montar ambiente para o teste de execution().\n");
		return (EXIT_FAILURE);
	}
	init_control_defaults();
	setup_execution_test();
	printf("Executando builtin \"echo\" com redirecionamento para %s\n", TEST_OUTFILE);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
	{
		perror("dup");
		return (EXIT_FAILURE);
	}
	execution();
	print_outfile();
	printf("exit_code: %d\n", te()->exit_code);
	printf("Arquivo gerado mantido em %s (remova manualmente se desejar).\n", TEST_OUTFILE);
	close(saved_stdout);
	return (EXIT_SUCCESS);
}

static int	run_export_test(void)
{
	char	env_pwd[] = "PWD=/tmp";
	char	env_lang[] = "LANG=C";
	char	*env_template[] = {env_pwd, env_lang, NULL};
	char	*argv_update[] = {"export", "NEWVAR=hello", "PWD=/var/minishell", NULL};
	char	*argv_multi[] = {"export", "MULTI_ONE=primeiro", "MULTI_TWO=segundo", "LOCAL_EXTRA=promovido", NULL};
	char	*argv_empty[] = {"export", "EMPTY=", "ONLY_EQUAL=", NULL};
	char	*argv_override[] = {"export", "MULTI_ONE=redefinido", "PWD=/tmp/override", NULL};
	char	*argv_repromote[] = {"export", "LOCAL_ONLY", NULL};
	char	*argv_list_sorted[] = {"export", NULL};
	char	*argv_duplicate_local[] = {"export", "LOCAL_EXTRA", NULL};
	char	*argv_no_local[] = {"export", "NOT_PRESENT", NULL};
	char	*argv_promote[] = {"export", "LOCAL_ONLY", NULL};
	char	*argv_list[] = {"export", NULL};

	cleanup();
	if (!mount_envp(env_template))
	{
		fprintf(stderr, "Erro ao montar ambiente para o teste de builtin_export().\n");
		return (EXIT_FAILURE);
	}
	init_control_defaults();
	if (te()->l_var)
	{
		free_doble_pointer(te()->l_var);
		te()->l_var = NULL;
	}
	create_local_variable("LOCAL_ONLY", "valor_local");
	create_new_local_var("LOCAL_EXTRA", "42");
	printf("=== Teste builtin_export() ===\n");
	print_vector("Ambiente inicial", te()->envp);
	print_vector("Variaveis locais iniciais", te()->l_var);
	builtin_export(argv_update);
	print_vector("Ambiente apos export NEWVAR=hello e PWD=/var/minishell", te()->envp);
	print_vector("Variaveis locais apos export com '='", te()->l_var);
	builtin_export(argv_multi);
	print_vector("Ambiente apos export MULTI_ONE=primeiro MULTI_TWO=segundo e LOCAL_EXTRA=promovido", te()->envp);
	print_vector("Variaveis locais apos export com multiplos argumentos", te()->l_var);
	builtin_export(argv_empty);
	print_vector("Ambiente apos export de variaveis com valor vazio", te()->envp);
	print_vector("Variaveis locais apos export de variaveis com valor vazio", te()->l_var);
	builtin_export(argv_no_local);
	print_vector("Ambiente apos tentar exportar variavel inexistente sem '='", te()->envp);
	print_vector("Variaveis locais apos tentar exportar variavel inexistente", te()->l_var);
	builtin_export(argv_override);
	print_vector("Ambiente apos sobrescrever variaveis existentes", te()->envp);
	print_vector("Variaveis locais apos sobrescrever variaveis existentes", te()->l_var);
	builtin_export(argv_duplicate_local);
	print_vector("Ambiente apos tentar promover LOCAL_EXTRA novamente", te()->envp);
	print_vector("Variaveis locais apos tentar promover LOCAL_EXTRA novamente", te()->l_var);
	builtin_export(argv_promote);
	print_vector("Ambiente apos export LOCAL_ONLY", te()->envp);
	print_vector("Variaveis locais apos promover LOCAL_ONLY", te()->l_var);
	builtin_export(argv_repromote);
	print_vector("Ambiente apos export LOCAL_ONLY (repetido)", te()->envp);
	print_vector("Variaveis locais apos export LOCAL_ONLY (repetido)", te()->l_var);
	printf("Saida formatada do export sem argumentos:\n");
	builtin_export(argv_list);
	printf("Saida final do export (duplicada para confirmar ordenacao):\n");
	builtin_export(argv_list_sorted);
	return (EXIT_SUCCESS);
}

static int	run_unset_test(void)
{
	char	env_pwd[] = "PWD=/tmp";
	char	env_lang[] = "LANG=C";
	char	env_keep[] = "KEEP=manter";
	char	env_remove[] = "REMOVE_ME=remover";
	char	*env_template[] = {env_pwd, env_lang, env_keep, env_remove, NULL};
	char	*argv_single[] = {"unset", "REMOVE_ME", NULL};
	char	*argv_multi[] = {"unset", "KEEP", "LOCAL_TEMP", "NOT_PRESENT", NULL};
	char	*argv_invalid[] = {"unset", "1INVALID", NULL};
	int		result;

	cleanup();
	if (!mount_envp(env_template))
	{
		fprintf(stderr, "Erro ao montar ambiente para o teste de builtin_unset().\n");
		return (EXIT_FAILURE);
	}
	init_control_defaults();
	if (te()->l_var)
	{
		free_doble_pointer(te()->l_var);
		te()->l_var = NULL;
	}
	create_local_variable("LOCAL_STAY", "permanece");
	create_new_local_var("LOCAL_TEMP", "temporario");
	create_new_local_var("LOCAL_EXTRA", "extra");
	printf("=== Teste builtin_unset() ===\n");
	print_vector("Ambiente inicial", te()->envp);
	print_vector("Variaveis locais iniciais", te()->l_var);
	result = builtin_unset(argv_single);
	printf("Resultado unset (um argumento): %s\n", bool_to_label(result));
	print_vector("Ambiente apos remover REMOVE_ME", te()->envp);
	print_vector("Variaveis locais apos remover REMOVE_ME", te()->l_var);
	result = builtin_unset(argv_multi);
	printf("Resultado unset (varios argumentos): %s\n", bool_to_label(result));
	print_vector("Ambiente apos remover KEEP e outros alvos", te()->envp);
	print_vector("Variaveis locais apos remover LOCAL_TEMP", te()->l_var);
	result = builtin_unset(argv_invalid);
	printf("Resultado unset com identificador invalido: %s\n", bool_to_label(result));
	print_vector("Ambiente apos tentativa invalida", te()->envp);
	print_vector("Variaveis locais apos tentativa invalida", te()->l_var);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 2)
	{
		fprintf(stderr, "Uso: %s <execution|export|unset>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (str_equals(argv[1], "execution"))
		status = run_execution_test(envp);
	else if (str_equals(argv[1], "export"))
		status = run_export_test();
	else if (str_equals(argv[1], "unset"))
		status = run_unset_test();
	else
	{
		fprintf(stderr, "Teste \"%s\" desconhecido. Opcoes validas: execution, export, unset\n", argv[1]);
		status = EXIT_FAILURE;
	}
	cleanup();
	return (status);
}
