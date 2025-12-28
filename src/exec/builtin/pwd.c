#include "../../../includes/minishell.h"

int    builtin_pwd(void)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if(!pwd)
    {
        pwd = join3(te()->cwd, NULL, NULL);
        if(!pwd)
        {
            te()->exit_code = 1;
            perror("pwd");
            return (FALSE);
        }
    }
    write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
    free(pwd);
    te()->exit_code = 0;
    return (TRUE);
}
