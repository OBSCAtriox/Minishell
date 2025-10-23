#include "../../../includes/minishell.h"

int splited_path(void)
{
    char    *path;

    path = NULL;
    if(!tc()->paths)
    {
        path = expand_variable("PATH", te()->envp);
        if(!path)
            return (FALSE);
        tc()->paths = ft_split(path, ':');
        if(!tc()->paths)
            return (FALSE);
        free(path);
    }
    return (TRUE);
}

char    *find_bin_path(char *arg)
{
    int i;
    char **paths;
    char *path_bin;

    i = 0;
    path_bin = NULL;
    paths = tc()->paths;
    while(paths[i])
    {
        path_bin = join3(paths[i], BAR, arg);
        if(!path_bin)
            return (NULL);
        if(access(path_bin, X_OK) == 0)
            return(path_bin);
        free(path_bin);
        i++;
    }
    return (NULL);
}

char    *path_to_binary(char *arg)
{
    char *path;

    path = NULL;
    if(!splited_path())
        return (print_error(arg, "failed to search enviroment"), NULL);
    if(ft_strchr(arg, '/'))
    {
        if(!check_path(arg))
            return (NULL);
        else
            return (arg);
    }
    else
    {
        path = find_bin_path(arg);
        if(!path)
        {
            tc()->exit_path = 127;
            return (print_error(arg, "command not found"), NULL);
        }
    }
    return (path);
}
