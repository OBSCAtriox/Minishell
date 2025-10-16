#include "../../../includes/minishell.h"

void    print_error(char *msg)
{
    write(2, "Error\n", 6);
    if (msg)
    {
        write(2, msg, ft_strlen(msg));
        write(2, "\n", 1);
    }
}

void    error_cd(char *arg)
{
    write(2, "cd: ", 4);
    perror(arg);
}

void    error_pwd(void)
{
    write(2, "minishell: ", 11);
    perror("PWD");
}
