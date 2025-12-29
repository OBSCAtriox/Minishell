#include "../../includes/minishell.h"

void    exit_heredoc(int fd_1)
{
    close(fd_1);
    cleanup();
    exit(0);
}