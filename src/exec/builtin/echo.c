#include "../../../includes/minishell.h"

int    builtin_echo(char **argv)
{
    int n_flag;
    int i;

    n_flag = 0;
    if(!argv)
    {
        write(1, "\n", 1);
        te()->exit_code = 0;
        return (FALSE);
    }
    i = 1;
    if(argv[i] && has_new_line(argv[i]))
        n_flag = 1;
    while(argv[i])
    {
        print_echo(argv, i);
        i++;
    }
    if(!n_flag)
        write(1, "\n", 1);
    te()->exit_code = 0;
    return (TRUE);
}

int has_new_line(char *arg)
{
    int i;

    i = 0;
    if(arg[0] == '-' && arg[1] == 'n')
    {
        i += 2;
        while(arg[i])
        {
            if(arg[i] != 'n')
                return (FALSE);
            i++;
        }
        return (TRUE);
    }
    return (FALSE);
}

void    print_echo(char **argv, int i)
{
    if(!has_new_line(argv[i]))
    {
        write(1, argv[i], ft_strlen(argv[i]));
        if(argv[i] && argv[i + 1])
            write(1, " ", 1);
    }
}
