#include "../../../includes/minishell.h"

int buitin_cd(char *argv)
{
    char    *old_pwd;
    char    *new_pwd;

    old_pwd = getcwd(NULL, 0);
    if(!old_pwd)
        return(error_cd(argv), -1);
    if (chdir(argv) == -1)
        return (error_cd(argv), -1);
    new_pwd = getcwd(NULL, 0);
    if(!new_pwd)
        return(error_cd(argv), -1);
    te()->oldpwd = ft_strdup(old_pwd);
    env_set("PWD", new_pwd);
    free(old_pwd);
    free(new_pwd);
    return (0);
}