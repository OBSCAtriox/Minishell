#include "../../../includes/minishell.h"

int builtin_cd(char **arg)
{
    char    *target;
    char    *old_pwd;
    char    *new_pwd;

    target = get_target(arg);
    if(!target)
        return (failed_cd(NULL, NULL, NULL), FALSE);
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
        return (failed_cd(NULL, &target, NULL), FALSE);
    if (chdir(target) == -1)
        return (failed_cd(NULL, &target, &old_pwd), FALSE);
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
        return (failed_cd(&new_pwd, &target, &old_pwd), FALSE);
    if (te()->oldpwd)
        free(te()->oldpwd);
    te()->oldpwd = old_pwd;
    env_set("PWD", new_pwd, te()->envp);
    free_cd(&new_pwd, &target, &old_pwd, 0);
    te()->exit_code = 0;
    return (TRUE);
}

char    *get_target(char **arg)
{
    char    *target;

    target = NULL;
    if (arg[1] && arg[2])
        return (print_error("cd", "too many arguments"), NULL);
    if (arg[1])
    {
        target = ft_strdup(arg[1]);
        if (!target)
            return (print_error("cd", "allocation failed"), NULL);
    }
    else
    {
        target = expand_variable("HOME", te()->envp);
        if (!target)
            return (print_error("cd", "HOME not set"), NULL);
    }
    return (target);
}

void    free_cd(char **new_pwd, char **target, char **old_pwd, int err)
{
    if (err && target && *target)
        error_cd(*target);
    if (new_pwd && *new_pwd)
    {
        free(*new_pwd);
        *new_pwd = NULL;
    }
    if (target && *target)
    {
        free(*target);
        *target = NULL;
    }
    if (old_pwd && *old_pwd)
    {
        if (err)
            free(*old_pwd);
        *old_pwd = NULL;
    }
}

void    failed_cd(char **new_pwd, char **target, char **old_pwd)
{
    free_cd(new_pwd, target, old_pwd, 1);
    te()->exit_code = 1;
}
