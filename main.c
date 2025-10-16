#include "includes/minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

static char	g_cd_cmd[] = "cd";
static char	g_exit_cmd[] = "exit";

t_env	*te(void)
{
	static t_env	env;

	return (&env);
}

static void	print_section(const char *title)
{
	printf("\n---- %s ----\n", title);
}

static void	show_var(const char *name)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (te()->envp && te()->envp[i])
	{
		if (ft_strncmp(te()->envp[i], name, len) == 0 && te()->envp[i][len] == '=')
		{
			printf("%s\n", te()->envp[i]);
			return ;
		}
		i++;
	}
	printf("%s is not set\n", name);
}

static void	test_echo(void)
{
	print_section("builtin echo");
	printf("echo \"hello world\"\n");
	built_echo("hello world");
	printf("echo \"-n no newline\"\n");
	built_echo("-n no newline");
	printf("echo NULL (should print newline)\n");
	built_echo(NULL);
	printf("echo \"   leading and trailing   \"\n");
	built_echo("   leading and trailing   ");
}

static void	test_pwd(void)
{
	print_section("builtin pwd");
	built_pwd();
}

static void	run_cd_case(const char *label, const char *path, const char *extra)
{
	char	*before;
	char	*after;
	char	*dup_path;
	char	*dup_extra;
	int		result;
	char	*argv[4];

	before = getcwd(NULL, 0);
	printf("%s\n", label);
	if (path)
	{
		printf("  target: %s\n", path);
		if (extra)
			printf("  extra arg: %s\n", extra);
	}
	else
		printf("  target: (null)\n");
	dup_path = path ? ft_strdup(path) : NULL;
	if (path && !dup_path)
	{
		perror("ft_strdup");
		free(before);
		printf("\n");
		return ;
	}
	dup_extra = extra ? ft_strdup(extra) : NULL;
	if (extra && !dup_extra)
	{
		perror("ft_strdup");
		free(before);
		free(dup_path);
		printf("\n");
		return ;
	}
	argv[0] = g_cd_cmd;
	argv[1] = dup_path;
	argv[2] = dup_extra;
	argv[3] = NULL;
	result = buitin_cd(argv);
	printf("  return code: %d\n", result);
	after = getcwd(NULL, 0);
	if (after)
	{
		printf("  cwd now: %s", after);
		if (before && strcmp(before, after) == 0)
			printf(" (unchanged)");
		printf("\n");
	}
	else
		perror("getcwd");
	printf("\n");
	free(before);
	free(after);
	free(dup_path);
	free(dup_extra);
}

static void	test_cd(void)
{
	char	*original;
	char	*home;

	print_section("builtin cd");
	original = getcwd(NULL, 0);
	home = expand_variable("HOME", te()->envp);
	if (original)
		printf("starting cwd: %s\n\n", original);
	if (home)
		run_cd_case("cd HOME", home, NULL);
	else
		printf("HOME not available, skipping HOME test\n\n");
	if (original)
		run_cd_case("cd back to original", original, NULL);
	run_cd_case("cd invalid path (expect error message)", "/this/path/should/fail", NULL);
	if (home)
		run_cd_case("cd too many args (should complain)", home, "extra");
	free(home);
	free(original);
}

static void	test_export_unset(void)
{
	print_section("builtin export/unset");
	printf("export MSH_TEST=42\n");
	builtin_export("MSH_TEST=42");
	show_var("MSH_TEST");
	printf("export EMPTY=\n");
	builtin_export("EMPTY=");
	show_var("EMPTY");
	printf("unset invalid identifier 1INVALID\n");
	if (!builtin_unset("1INVALID"))
		printf("  rejected invalid identifier 1INVALID\n");
	if (te()->l_var && te()->l_var[0])
	{
		printf("local before export: %s\n", te()->l_var[0]);
		printf("export LOCAL_ONLY\n");
		builtin_export("LOCAL_ONLY");
		show_var("LOCAL_ONLY");
	}
	else
		printf("no local variable available for export\n");
	printf("cleanup exported variables\n");
	builtin_unset("MSH_TEST");
	builtin_unset("EMPTY");
	builtin_unset("LOCAL_ONLY");
	show_var("MSH_TEST");
	show_var("EMPTY");
	show_var("LOCAL_ONLY");
	printf("\n");
}

static void	test_env_listing(void)
{
	print_section("builtin export/env listing");
	printf("export XXX=\n");
	builtin_export("XXX=");
	show_var("XXX");
	printf("\nexport with no args (sorted)\n");
	builtin_export(NULL);
	printf("\n");
	printf("env\n");
	builtin_env();
	builtin_unset("XXX");
	printf("\n");
}

static void	run_exit_case(const char *label, const char *arg1, const char *arg2, int expect_exit, int expected_status)
{
	pid_t	pid;
	int		status;
	char	*argv[4];
	char	*dup_arg1;
	char	*dup_arg2;

	printf("%s\n", label);
	if (arg1)
	{
		printf("  arg1: %s\n", arg1);
		if (arg2)
			printf("  arg2: %s\n", arg2);
	}
	dup_arg1 = arg1 ? ft_strdup(arg1) : NULL;
	if (arg1 && !dup_arg1)
	{
		perror("ft_strdup");
		printf("\n");
		return ;
	}
	dup_arg2 = arg2 ? ft_strdup(arg2) : NULL;
	if (arg2 && !dup_arg2)
	{
		perror("ft_strdup");
		free(dup_arg1);
		printf("\n");
		return ;
	}
	argv[0] = g_exit_cmd;
	argv[1] = dup_arg1;
	argv[2] = dup_arg2;
	argv[3] = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(dup_arg1);
		free(dup_arg2);
		printf("\n");
		return ;
	}
	if (pid == 0)
	{
		if (expect_exit)
		{
			builtin_exit(argv);
			_exit(127);
		}
		builtin_exit(argv);
		_exit(201);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		free(dup_arg1);
		free(dup_arg2);
		printf("\n");
		return ;
	}
	if (expect_exit)
	{
		if (WIFEXITED(status))
		{
			int	code;

			code = WEXITSTATUS(status);
			printf("  child exit code: %d", code);
			if (expected_status >= 0 && code != expected_status)
				printf(" (expected %d)", expected_status);
			printf("\n");
		}
		else if (WIFSIGNALED(status))
			printf("  child terminated by signal %d\n", WTERMSIG(status));
	}
	else
	{
		if (WIFEXITED(status))
			printf("  builtin_exit returned, child exit code %d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("  child terminated by signal %d\n", WTERMSIG(status));
	}
	free(dup_arg1);
	free(dup_arg2);
	printf("\n");
}

static void	test_exit(void)
{
	print_section("builtin exit");
	te()->exit_code = 21;
	run_exit_case("exit with no args (uses te()->exit_code)", NULL, NULL, 1, 21);
	run_exit_case("exit 7", "7", NULL, 1, 7);
	run_exit_case("exit invalid numeric", "abc", NULL, 1, 255);
	run_exit_case("exit too many args (should not exit)", "1", "2", 0, 0);
	te()->exit_code = 0;
}

static void	cleanup(void)
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!mount_envp(envp))
	{
		fprintf(stderr, "failed to duplicate environment\n");
		return (1);
	}
	te()->exit_code = 0;
	setvbuf(stdout, NULL, _IONBF, 0);
	create_local_variable("LOCAL_ONLY", "value");
	if (!te()->l_var)
		printf("failed to seed local variables\n");
	test_echo();
	test_pwd();
	test_cd();
	test_export_unset();
	test_env_listing();
	test_exit();
	cleanup();
	return (0);
}
