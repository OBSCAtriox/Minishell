#include "../../includes/minishell.h"

void    heredoc(void)
{
    t_data dt;
    t_cmd   **cmdv;
    t_redir **redir;

    dt.i = 0;
    cmdv = tp()->cmdv;
    while(cmdv[dt.i])
    {
        redir = cmdv[dt.i]->redir;
        dt.j = 0;
        while (redir && redir[dt.j])
        {
            if(redir[dt.j]->type == R_HDOC)
                mount_heredoc(dt.i, dt.j);
            dt.j++;
        }
        dt.i++;
    }
}

int    mount_heredoc(int idx_cmd, int idx_rdir)
{
    int fd[2];
    pid_t pid;
    char    *delim;

    delim = tp()->cmdv[idx_cmd]->redir[idx_rdir]->path;
    if(pipe(fd) < 0)
    {
        perror("pipe");
        return (FALSE);
    }
    pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return (FALSE);
    }
    else if(pid == 0);
        read_heredoc(idx_cmd, idx_rdir, fd, delim);
    waitpid();
}

void    read_heredoc(int idx_cmd, int idx_rdir, int *fd, char *delim)
{
    char    *line;
    int     quoted;
    char    *exp;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    close(fd[0]);
    quoted = tp()->cmdv[idx_cmd]->redir[idx_rdir]->quoted;
    while (1)
    {
        line = readline("> ");
        if(!line)
            break;
        if(ft_strncmp(line, delim, ft_strlen(line) == 0))
        {
            free(line);
            break;
        }
        if(!quoted)
            write_line(quoted, line, fd[1]);
        else
            ft_putendl_fd(line, fd[1]);
        free(line);
    }

}

void    write_line(int quoted, char *line, int fd)
{
    char *exp;

    if(!quoted)
    {
        exp = expand_line(line);
        if(!exp)
        {
            free(line);
            exit (1);
        }
        ft_putendl_fd(exp, fd);
    }
    else
        ft_putendl_fd(line, fd);
}
