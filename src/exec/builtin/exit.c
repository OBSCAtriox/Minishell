#include "../../../includes/minishell.h"

int    builtin_exit(char **arg)
{
    long long    code;

    if(!arg[1])
        code = te()->exit_code;
    else if(arg[2])
    {
        if(tc()->in_parent)
            write(1, "exit\n", 5);
        print_error("exit", "too many arguments");
        te()->exit_code = 1;
        return (FALSE);
    }
    else
    {
        if(!check_number(arg[1]))
            code = 2;
        else
            code = ft_atoi(arg[1]) % 256;
    }
    if(tc()->in_parent)
    {
        restore_std();
        cleanup();
    }
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

int check_number(char *arg)
{
    int sign;
    unsigned long long result;
    int i;

    i = 0;
    sign = 0;
    result = 0;
    if(arg[i] == '-' || arg[i] == '+')
    {
        if(arg[i] == '-')
            sign = 1;
        i++;
    }
    while(arg[i])
    {
        if(!ft_isdigit(arg[i]))
            return (print_error("exit", "numeric argument required"), FALSE);
        result = result * 10 + (arg[i] - '0');
        i++;
    }
    if(sign && result > ((unsigned long long)LLONG_MAX + 1))
        return (print_error("exit", "numeric argument required"), FALSE);
    else if(!sign && result > (unsigned long long)LLONG_MAX)
        return (print_error("exit", "numeric argument required"), FALSE);
    return (TRUE);
}
