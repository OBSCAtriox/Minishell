#include "../../../includes/minishell.h"

void    builtin_export(char *argv)
{
    char    *name;
    char    *value;

    if(!argv)
        return (print_export());
    if(is_valid_indentifier(argv))
    {
        name = get_name_var(argv);
        value = get_value_var(argv);
        if(has_equal(argv) && !value)
            env_set(name, "", te()->envp);
        else if(!has_equal(argv) && !value)
            export_variable(name);
    }
}

void    print_export(void)
{
    char    **env;
    int     count;
    int     printed_count;
    int     *printed;
    int     next;

    env = te()->envp;
    count = size_vetor(env);
    printed = ft_calloc(count, sizeof(int));
    if(!printed)
        return ;
    printed_count = 0;
    while (printed_count < count)
    {
        next = find_next_min(env, printed);
        if(next == -1)
            break;
        print_export_line(env[next]);
        printed[next] = 1;
        printed_count++;
    }
    free(printed);
}

int is_valid_indentifier(char *arg)
{
    if((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')
        || arg[0] == '_')
        return (TRUE);
    else
        return (FALSE);
}

void    export_variable(char *arg)
{
    int index;
    char    *var;
    char    *name;
    char    *value;

    index = find_variable(arg, te()->l_var);
    if(index == -1)
        return;
    else
    {
        var = te()->l_var[index];
        name = get_name_var(var);
        value = get_value_var(var);
        env_set(name, value, te()->envp);
    }
}
