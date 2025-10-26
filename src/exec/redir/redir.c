#include "../../../includes/minishell.h"

int    redir(t_cmd *cmdv)
{
    t_data dt;
    t_redir **redir;

    dt.i = 0;
    redir = cmdv->redir;
    if(!redir)
        return (FALSE);
    while(redir && redir[dt.i])
    {
        if(redir[dt.i]->type == R_IN || redir[dt.i]->type == R_HDOC)
        {
            if(apply_redir_in(redir[dt.i]) == FALSE)
                return (FALSE);
        }
        else if(redir[dt.i]->type == R_OUT || redir[dt.i]->type == R_APP)
        {
            if(apply_redir_out(redir[dt.i]) == FALSE)
                return (FALSE);
        }
        dt.i++;
    }
    return (TRUE);
}

int apply_redir_in(t_redir *redir)
{
    int target;
    int fd;

    target = redir->fd_target;
    fd = -1;
    if(redir->type == R_IN)
    {
        fd = open(redir->path, O_RDONLY);
        if(fd < 0)
            return (perror(redir->path), FALSE);
    }
    else if(redir->type == R_HDOC)
    {
        fd = dup(redir->hdoc_fd);
        if(fd < 0)
            return (perror("hdoc"), FALSE);
        close(redir->hdoc_fd);
    }
    if(fd >= 0)
    {
        if(dup2(fd, target) < 0)
            return(close(fd), perror("dup2"), FALSE);
        close(fd);
    }
    return (TRUE);
}

int apply_redir_out(t_redir *redir)
{
    int target;
    int fd;

    target = redir->fd_target;
    fd = -1;
    if(redir->type == R_OUT)
    {
        fd = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd < 0)
            return (perror(redir->path), FALSE);
    }
    else if(redir->type == R_APP)
    {
        fd = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if(fd < 0)
            return (perror(redir->path), FALSE);
    }
    if(fd >= 0)
    {
        if(dup2(fd, target) < 0)
            return(close(fd), perror("dup2"), FALSE);
        close(fd);
    }
    return (TRUE);
}

int make_dup_pipe(int *fd, int temp_fd, int has_next)
{
    if (temp_fd != -1) 
    {
        if (dup2(temp_fd, STDIN_FILENO) < 0) 
        { 
            close_all(fd[1], fd[0], temp_fd, -1);
            perror("dup2 in"); 
            return (FALSE); 
        }
    }
    if (has_next)
    {
        if (dup2(fd[1], STDOUT_FILENO) < 0) 
        { 
            close_all(fd[1], fd[0], temp_fd, -1);
            perror("dup2 out"); 
            return(FALSE);
        }
    }
    return (TRUE);
}
