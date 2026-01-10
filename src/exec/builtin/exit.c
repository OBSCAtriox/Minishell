#include "../../../includes/minishell.h"

static int check_valid_arg(char *arg)
{
    if(!arg || arg[0] == '\0')
    {
        print_error("exit", "numeric argument required");
        return (FALSE);
    }
    return (TRUE);
}

static void check_after_two_arg(char *arg)
{
    if(!ft_isdigit(arg[1]))
    {
        if(tc()->in_parent)
            write(1, "exit\n", 5);
        print_error("exit", "numeric argument required");
        if(tc()->in_parent)
        {
            restore_std();
            cleanup();
        }
        exit(2);
    }
}

static int more_than_one(char **arg)
{
    check_after_two_arg(arg[1]);
    if(tc()->in_parent)
        write(1, "exit\n", 5);
    print_error("exit", "too many arguments");
    te()->exit_code = 1;
    return (FALSE);
}

int    builtin_exit(char **arg)
{
    long long    code;

    if(!arg[1])
        code = te()->exit_code;
    else if(arg[2])
    {
        if(!more_than_one(arg))
            return (FALSE);
    }
    else
    {
        if(!check_valid_arg(arg[1]) || !check_number(arg[1]))
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

int check_number(char *arg)
{
    int sign;
    unsigned long long result;
    int i;

    i = 0;
    sign = 0;
    result = 0;
    if((arg[i] == '-' || arg[i] == '+') && arg[i + 1])
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
