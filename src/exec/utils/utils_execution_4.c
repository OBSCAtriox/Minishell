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
