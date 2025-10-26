#include "../../../includes/minishell.h"

void    builtin_pwd(void)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if(!pwd)
    {
        te()->exit_code = 1;
        perror("pwd");
        return ;
    }
    write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
    free(pwd);
    te()->exit_code = 0;
}
