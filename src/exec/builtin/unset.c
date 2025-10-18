#include "../../../includes/minishell.h"

int builtin_unset(char  *arg)
{
    int     index;

    if(!is_valid_identifier(arg))
        return (FALSE);
    index = find_variable(arg, te()->envp);
    if(index != -1)
        remove_env_var(index);
    index = find_variable(arg, te()->l_var);
        remove_local_var(index);
    return (TRUE);
}

int remove_env_var(int index)
{
    t_data dt;

    dt.size = size_vetor(te()->envp);
    dt.env = malloc(sizeof(char *) * (dt.size + 1));
    if(!dt.env)
        return (FALSE);
    dt.i = 0;
    dt.j = 0;
    while(te()->envp[dt.i])
    {
        if(skip_var_dell(index, &dt.i))
            continue;
        dt.env[dt.j] = ft_strdup(te()->envp[dt.i]);
        if(!dt.env[dt.j])
            return (free_vetor_failed(dt.env, dt.j), FALSE);
        dt.i++;
        dt.j++;
    }
    dt.env[dt.j] = NULL;
    free_doble_pointer(te()->envp);
    if(!mount_envp(dt.env))
        return (free_doble_pointer(dt.env), FALSE);
    free_doble_pointer(dt.env);
    return (TRUE);
}

int remove_local_var(int index)
{
    t_data dt;

    dt.size = size_vetor(te()->l_var);
    dt.env = malloc(sizeof(char *) * (dt.size + 1));
    if(!dt.env)
        return (FALSE);
    dt.i = 0;
    dt.j = 0;
    while(te()->l_var[dt.i])
    {
        if(skip_var_dell(index, &dt.i))
            continue;
        dt.env[dt.j] = ft_strdup(te()->l_var[dt.i]);
        if(!dt.env[dt.j])
            return (free_vetor_failed(dt.env, dt.j), FALSE);
        dt.i++;
        dt.j++;
    }
    dt.env[dt.j] = NULL;
    free_doble_pointer(te()->l_var);
    if(!re_mount_locar_var(dt.env))
        return (free_doble_pointer(dt.env), FALSE);
    free_doble_pointer(dt.env);
    return (TRUE);
}

int    skip_var_dell(int index, int *i)
{
    if(index == *i)
    {
        (*i)++;
        return (TRUE);
    }
    return (FALSE);
}
