#include "../../includes/minishell.h"

int    builtin_in_parent_process(void)
{
    if(tc()->num_cmd == 1 && ms()->cmdv[0]->is_builtin)
    {
        clone_std();
        redir(ms()->cmdv[0]);
        call_builtin(ms()->cmdv[0]->argv);
        restore_std();
        return (TRUE);
    }
    return (FALSE);
}

int    exec_pipeline(void)
{
    t_data dt;
    t_cmd **cmdv;
    int     has_next;

    inits_pipeline(&dt);
    cmdv = ms()->cmdv;
    has_next = 1;
    while(cmdv[dt.i])
    {
        check_last_comand(dt, &has_next);
        if(dt.i < tc()->num_cmd - 1)
        {
            if(pipe(dt.fd) == -1)
                return(perror("pipe"), FALSE);
        }
        dt.pid = safe_fork();
        if (dt.pid == 0)
            process_children(cmdv[dt.i], dt.fd, dt.temp_fd, has_next);
        parent_step(&dt);
        dt.i++;
    }
    if(dt.temp_fd != -1)
        close(dt.temp_fd);
    wait_for_children(tc()->last_pid);
    return (TRUE);
}

void    process_children(t_cmd *cmdv, int *fd, int temp_fd, int has_next)
{
    char    **envp;
    char    *path;

    envp = te()->envp;
    safe_path(&path, fd, temp_fd, cmdv);
    if(!make_dup_pipe(fd, temp_fd, has_next))
    {
        free(path);
        exit(1);
    }
    if(!redir(cmdv))
    {
        close_all(fd[0], fd[1], temp_fd, -1);
        free(path);
        exit(1);
    }
    close_all(fd[0], fd[1], temp_fd, -1);
    execve(path, cmdv->argv, envp);
    perror(cmdv->argv[0]);
    free(path);
    exit(127);
}

void    execution(void)
{
    count_cmd();
    if(!heredoc())
        return ;
    if(builtin_in_parent_process())
        return;
    exec_pipeline();
    free_pipeline();
}
