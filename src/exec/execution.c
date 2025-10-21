#include "../../includes/minishell.h"

t_control   *tc(void)
{
    static t_control control;
    
    return(&control);
}

void    count_cmd(void)
{
    int i;

    i = 0;
    while(tp()->cmdv[i])
        i++;
    tc()->num_cmd = i;
}

void    builtin_in_parent_process(void)
{
    if(tc()->num_cmd == 1 && tp()->cmdv[0]->is_builtin)
    {
        clone_std();
        redir(tp()->cmdv[0]);
        call_builtin(tp()->cmdv[0]->argv);
        restore_std();
    }
}

void    execution(void)
{
    count_cmd();
    heredoc();
    builtin_in_parent_process();
}
