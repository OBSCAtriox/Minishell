#include "../../../includes/minishell.h"

int  not_sum(char *name, char *value, char **env)
{
    int index;

    index = find_variable(name, env);
    if(index == -1)
    {
        env_set(name, value, env);
        return (FALSE);
    }
    return (TRUE);
}

int check_sum_and_set(char *name, char *value, char **env)
{
    char *new_value;
    char *old_value;

    if(tc()->sum_export)
    {
        if(!not_sum(name, value, env))
            return (FALSE);
        old_value = expand_variable(name, env);
        new_value = join3(old_value, value, NULL);
        if(!new_value || !old_value)
            return (FALSE);
        if(!env_set(name, new_value, env))
            return (free(old_value), free(new_value), FALSE);
        free(old_value);
        free(new_value);
    }
    else
    {
        if(!env_set(name, value, env))
            return (FALSE);
    }
    return (TRUE);
}

void    aux_export_two(char *arg, int *signaled_exit)
{
    write(2, "export: ", 8);
    print_error(arg, "not a valid identifier");
    te()->exit_code = 1;
    *signaled_exit = TRUE;
}
