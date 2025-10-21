#include "../../../includes/minishell.h"

void    builtin_echo(char *arg)
{
    int n_flag;
    int i;

    if(!arg)
    {
        write(1, "\n", 1);
        return ;
    }
    i = 0;
    if(arg[0] == '-' && arg[1] == 'n' && arg[2] == 32)
    {
        n_flag = 1;
        i += 2;
    }
    else
        n_flag = 0;
    while(arg[i] == 32)
        i++;
    while (arg[i])
    {
        write(1, &arg[i], 1);
        i++;
    }
    if(!n_flag)
        write(1, "\n", 1);
}
