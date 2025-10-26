#include "../../../includes/minishell.h"

t_control   *tc(void)
{
    static t_control control;
    
    return(&control);
}

void    inits_pipeline(t_data *dt)
{
    dt->i = 0;
    dt->fd[0] = -1;
    dt->fd[1] = -1;
    dt->temp_fd = -1;
    tc()->last_pid = -1;
}

pid_t safe_fork(void)
{
    pid_t pid;

    pid = fork();
    if(pid < 0)
        return (perror("fork"), pid);
    return (pid);
}

void    parent_step(t_data *dt)
{
    if(dt->fd[1] != -1)
        close(dt->fd[1]);
    if(dt->temp_fd != -1)
        close(dt->temp_fd);
    dt->temp_fd = dt->fd[0];
    dt->fd[0] = -1;
    dt->fd[1] = -1;
    if(dt->i == tc()->num_cmd)
        tc()->last_pid = dt->pid;
}

void    close_all(int fd_1, int fd_2, int fd_3, int fd_4)
{
    if(fd_1 != -1)
        close(fd_1);
    if(fd_2 != -1)
        close(fd_2);
    if(fd_3 != -1)
        close(fd_3);
    if(fd_4 != -1)
        close(fd_4);
}
