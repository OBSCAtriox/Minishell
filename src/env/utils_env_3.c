#include "../../includes/minishell.h"

int    create_new_local_var(char *name, char *value)
{
    t_data dt;

    dt.size = size_vetor(te()->l_var);
    dt.env = malloc(sizeof(char *) * (dt.size + 2));
    if(!dt.env)
        return (FALSE);
    dt.i = 0;
    while(dt.i < dt.size)
    {
        dt.env[dt.i] = ft_strdup(te()->l_var[dt.i]);
        if(!dt.env[dt.i])
            return (free_vetor_failed(dt.env, dt.i), FALSE);
        dt.i++;
    }
    dt.env[dt.size] = join3(name, EQUAL, value);
    if(!dt.env[dt.size])
        return(free_doble_pointer(dt.env), FALSE);
    dt.env[dt.size + 1] = NULL;
    if(!re_mount_locar_var(dt.env))
        return(free_doble_pointer((dt.env)), FALSE);
    free_doble_pointer(dt.env);
    return (TRUE);
}

int    re_mount_locar_var(char **envp)
{
    int size;
    int i;
    
    i = 0;
    size = size_vetor(envp);
    te()->l_var = malloc(sizeof(char *) * (size + 1));
    if(!te()->l_var)
        return (FALSE);
    while(envp[i])
    {
        te()->l_var[i] = ft_strdup(envp[i]);
        if(!te()->envp[i])
        {
            free_vetor_failed(te()->l_var, i);
            return (FALSE);
        }
        i++;
    }
    te()->l_var[i] = NULL;
    return (TRUE);
}

void    inits_min_var(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if(!pwd)
        return (perror("pwd"));
    env_set("PWD", pwd, te()->envp);
    free(pwd);
}
