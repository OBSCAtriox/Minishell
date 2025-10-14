#include "../../../includes/minishell.h"

int buitin_cd(char *argv)
{
    char    *old_pwd;
    char    *new_pwd;
    char    *arg_path;

    arg_path = ft_strdup(argv);
    old_pwd = getcwd(NULL, 0);
    if(!old_pwd)
        return(error_cd(argv), -1);
    if(arg_path == NULL)
        arg_path = expand_variable("HOME", te()->envp);
    if (chdir(arg_path) == -1)
        return (error_cd(arg_path), -1);
    new_pwd = getcwd(NULL, 0);
    if(!new_pwd)
        return(error_cd(argv), -1);
    te()->oldpwd = ft_strdup(old_pwd);
    env_set("PWD", new_pwd, te()->envp);
    if(arg_path)
        free(arg_path);
    free(old_pwd);
    free(new_pwd);
    return (0);
}
