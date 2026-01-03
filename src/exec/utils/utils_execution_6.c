#include "../../../includes/minishell.h"

void    process_fail(int *fd, int temp_fd, char **path)
{
    close_all(fd[0], fd[1], temp_fd, -1);
    clean_redir_fd();
    cleanup();
    free(*path);
    exit(1);
}