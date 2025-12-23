#include "../../../includes/minishell.h"

void check_sum_local_var(char *name, char *value)
{
    char *new_value;
    char *old_value;
    int index;

    if(tc()->sum_export)
    {
        index = find_variable(name, te()->l_var);
        if(index == -1)
        {
            update_local_var(name, value);
            return;
        }
        old_value = expand_variable(name, te()->l_var);
        new_value = join3(old_value, value, NULL);
        if(!new_value || !old_value)
            return;
        update_local_var(name, new_value);
        free(old_value);
        free(new_value);
    }
    else
        update_local_var(name, value);
}

void call_update_var(char *name, char *value)
{
    int idx;

    idx = find_variable(name, te()->envp);
    if (idx != -1)
    {
        if (!check_sum_and_set(name, value, te()->envp))
            return;
        idx = find_variable(name, te()->l_var);
        if (idx != -1)
            remove_local_var(idx);
        idx = find_variable(name, te()->var_exp);
        if (idx != -1)
            remove_var_exp(idx);
        return;
    }
    idx = find_variable(name, te()->var_exp);
    if (idx != -1)
    {
        if (!check_sum_and_set(name, value, te()->envp))
            return;
        remove_var_exp(idx);
        return;
    }
    check_sum_local_var(name, value);
}

void    shell_level(void)
{
    int index;
    int value;
    char *exp_value;
    char *str_value;

    index = find_variable("SHLVL", te()->envp);
    if(index == -1)
    {
        env_set("SHLVL", "1", te()->envp);
        return;
    }
    exp_value = expand_variable("SHLVL", te()->envp);
    if(!exp_value || !ft_isnumeric(exp_value))
    {
        env_set("SHLVL", "1", te()->envp);
        return;
    }
    value = ft_atoi(exp_value);
    value += 1;
    str_value = ft_itoa(value);
    env_set("SHLVL", str_value, te()->envp);
    free(exp_value);
    free(str_value);
}

int    add_check_vars(t_cmd **cmdv)
{
    int i;
    char **argv;

    i = 0;
    argv = cmdv[0]->argv;
    while(argv[i])
    {
        if(is_valid_identifier(argv[i]))
        {
            if(!local_var(argv[i]))
                return (FALSE);
        }
        i++;
    }
    return (TRUE);
}
