#include "../../../includes/minishell.h"

void    define_limits_exit(unsigned long long *limit, int sign)
{
    if (sign)
        *limit = (unsigned long  long)LLONG_MAX + 1;
    else
        *limit = (unsigned long long)LLONG_MAX;
}

void    print_exit(void)
{
    if(tc()->in_parent)
        write(1, "exit\n", 5);
}