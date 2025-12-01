#include "../../../includes/minishell.h"

void    builtin_exit(char **arg)
{
    long    code;

    if(!arg[1])
        code = te()->exit_code;
    else if(!ft_isnumeric(arg[1]))
    {
        print_error("exit", "numeric argument required");
        code = 255;
    }
    else if(arg[2])
    {
        print_error("exit", "too many arguments");
        return ;
    }
    else
        code = ft_atoi(arg[1]) % 256;
    printf("Exit\n");
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
