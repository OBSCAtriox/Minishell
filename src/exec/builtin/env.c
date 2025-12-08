#include "../../../includes/minishell.h"

int builtin_env(void)
{
    int i;
    int size;
    char    *name;
    char    *value;

    i = 0;
    size = size_vetor(te()->envp);
    while(i < size)
    {
        name = get_name_var(te()->envp[i]);
        value = get_value_var(te()->envp[i]);
        if(value)
        {
            write(1, name, ft_strlen(name));
            write(1, "=", 1);
            write(1, value, ft_strlen(value));
            write(1, "\n", 1);
        }
        free(name);
        free(value);
        i++;
    }
    te()->exit_code = 0;
    return (TRUE);
}
