#include "../../../includes/minishell.h"

void    clean_redir_fd(void)
{
    t_cmd **cmdv;
    t_redir **redir;
    int i;

    cmdv = ms()->cmdv;
    if(!cmdv)
        return;
    i = 0;
    while (cmdv[i])
    {
        redir = cmdv[i]->redir;
        if (redir)
        {
            clean_redir(redir);
            cmdv[i]->redir = NULL;
        }
        i++;
    }
}
