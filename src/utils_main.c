#include "../includes/minishell.h"

void    initis_main(int argc, char **argv, char **envp)
{
    (void)argv;
	tc()->g_sig = 0;
	if (argc != 1)
		basic_error(ERR_ARG);
	mount_envp(envp);
	shell_level();
	set_cwd();
}

int readline_and_check(void)
{
    ps()->line = readline("\001\033[1;32m\002T_Shell> \001\033[0m\002");
	if (!ps()->line)
	{
		write(1, "exit\n", 5);
		return (FALSE);
	}
    return (TRUE);
}

int check_sigint(void)
{
    if(tc()->g_sig == SIGINT && ps()->line && ps()->line[0] == '\0')
	{
    	tc()->g_sig = 0;
    	free(ps()->line);
    	return (TRUE);
	}
    tc()->g_sig = 0;
    return (FALSE);
}

int empty_line(void)
{
    if (ps()->line[0] == '\0')
	{
		free(ps()->line);
		return (TRUE);
	}
    return (FALSE);
}

void    exit_main(void)
{
    rl_clear_history();
	cleanup();
	exit(te()->exit_code);
}
