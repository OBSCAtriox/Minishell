#include "../../../includes/minishell.h"

int    builtin_exit(char **arg)
{
    long    code;

    if(!arg[1])
        code = te()->exit_code;
    else if(!ft_isnumeric(arg[1]))
    {
        print_error("exit", "numeric argument required");
        code = 2;
    }
    else if(arg[2])
    {
        if(tc()->in_parent)
            write(1, "exit\n", 5);
        print_error("exit", "too many arguments");
        te()->exit_code = 1;
        return (FALSE);
    }
    else
        code = ft_atoi(arg[1]) % 256;
    if(tc()->in_parent)
        cleanup();
    exit(code);
}

int ft_isnumeric(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] < 48 || str[i] > 57)
            return (FALSE);
        i++;
    }
    return (TRUE);
}
