#include "../../../includes/minishell.h"

void call_update_var(char *name, char *value)
{
    int idx;

    idx = find_variable(name, te()->envp);
    if (idx != -1)
    {
        if (!env_set(name, value, te()->envp))
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
        if (!env_set(name, value, te()->envp))
            return;
        remove_var_exp(idx);
        return;
    }
    update_local_var(name, value);
}
