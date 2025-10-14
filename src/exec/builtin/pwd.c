#include "../../../includes/minishell.h"

void    built_pwd(void)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if(!pwd)
        return (error_pwd());
    write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
    free(pwd);
}