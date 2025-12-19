#include "../../../includes/minishell.h"

void    safe_path(char **path, int *fd, int temp_fd, t_cmd *cmdv)
{
    *path = path_to_binary(cmdv->argv[0]);
    if(!*path && !check_builtin(cmdv->argv[0]))
    {
        close_all(fd[0], fd[1], temp_fd, -1);
        exit(tc()->exit_path);
    }
}

void    check_last_comand(t_data dt, int *has_next)
{
    if(dt.i == tc()->num_cmd - 1)
        *has_next = 0;
}

void    wait_for_children(pid_t last_pid)
{
	int		status;
	int		exit_code;
	pid_t	wpid;

	exit_code = 0;
	wpid = 1;
	while (wpid > 0)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
	}
	te()->exit_code = exit_code;
    tc()->last_pid = 1;
}

int	check_builtin(char *arg)
{
    char *command;

    if (!arg)
        return (FALSE);
    command = arg;
    if (is_builtin(command, "echo"))
        return (TRUE);
    else if (is_builtin(command, "cd"))
        return (TRUE);
    else if (is_builtin(command, "env"))
        return (TRUE);
    else if (is_builtin(command, "pwd"))
        return (TRUE);
    else if (is_builtin(command, "unset"))
        return (TRUE);
    else if (is_builtin(command, "export"))
        return (TRUE);
    else if (is_builtin(command, "exit"))
        return (TRUE);
    return (FALSE);
}

int local_var(char *arg)
{
    char *name;
    char *value;

    if(!has_equal(arg))
        return (FALSE);
    name = get_name_var(arg);
    value = get_value_var(arg);
    if(!name)
    {
        free(name);
        free(value);
        return (FALSE);
    }
    if(value)
        call_update_var(name, value);
    free(name);
    free(value);
    return (TRUE);
}
