#include "../../includes/minishell.h"

void    initis_exp_find_var(t_data *dt, char *line)
{
    dt->i = 0;
    dt->k = 0;
    dt->count = count_var(line);
}

void    free_expand_line(t_data *dt, char ***exp)
{
    if(dt->len_p)
        free(dt->len_p);
    if(dt->index_p)
        free(dt->index_p);
    if(*exp)
        free_doble_pointer(*exp);
}

void wait_heredoc(pid_t pid, int *fd)
{
    int status;
    int sig;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        sig = WEXITSTATUS(status);
        if (sig == 130)
        {
            printf("\n");
            tc()->signaled_heredoc = 1;
            if(fd[0] > 0)
                close(fd[0]);
            if(fd[1] > 0)
                close(fd[1]);
            close_fd_redir();
            te()->exit_code = 130;
        }
        else
            te()->exit_code = WEXITSTATUS(status);
    }
}

void    close_fd_redir(void)
{
    t_data dt;
    t_cmd **cmdv;
    t_redir **redir;

    dt.i = 0;
    cmdv = tp()->cmdv;
    while(cmdv[dt.i])
    {
        redir = cmdv[dt.i]->redir;
        dt.j = 0;
        while (redir && redir[dt.j])
        {
            if(redir[dt.j]->hdoc_fd > 0)
                close(redir[dt.j]->hdoc_fd);
            tp()->cmdv[dt.i]->redir[dt.j]->hdoc_fd = -1;
            dt.j++;
        }
        dt.i++;
    }
}

void sigint_hdoc(int sig)
{
    (void)sig;
    if (tc()->hdoc_wfd >= 0)
        close(tc()->hdoc_wfd);
    exit(130);
}
