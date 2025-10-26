#include "../../../includes/minishell.h"

int builtin_unset(char  **argv)
{
    int     i;

    if(!argv)
        return (FALSE);
    i = 1;
    while(argv[i])
    {
        if(is_valid_identifier(argv[i]))
        {
            if(aux_unset(argv, i))
                te()->exit_code = 0;
            else
                te()->exit_code = 1;
        }
        else
        {
            te()->exit_code = 1;
            write(2, "unset: ", 7);
            print_error(argv[i], "not a valid identifier");
        }
        i++;
    }
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

int aux_unset(char **argv, int i)
{
    int index;

    index = find_variable(argv[i], te()->envp);
    if(index != -1)
    {
        if(!remove_env_var(index))
            return (FALSE);
    }
    index = find_variable(argv[i], te()->l_var);
    if(index != -1)
    {
        if(!remove_local_var(index))
            return (FALSE);
    }
    return (TRUE);
}
