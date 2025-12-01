#include "../../../includes/minishell.h"

void    safe_path(char **path, int *fd, int temp_fd, t_cmd *cmdv)
{
    *path = path_to_binary(cmdv->argv[0]);
    if(!*path)
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
