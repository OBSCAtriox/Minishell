#include "../../../includes/minishell.h"

void    builtin_export(char *argv)
{
    char    *name;
    char    *value;

    if(!argv)
        return (print_export());
    if(is_valid_identifier(argv))
    {
        name = get_name_var(argv);
        value = get_value_var(argv);
        if(has_equal(argv) && !value)
            env_set(name, "", te()->envp);
        else if(!has_equal(argv) && !value)
            export_variable(name);
        else
            if(!env_set(name, value, te()->envp))
                return (print_error("error exportin variable"));
    }
    free(name);
    free(value);
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

int is_valid_identifier(char *arg)
{
    int i;
    int first_character;
    int other_character;
    int len;

    first_character = FALSE;
    other_character = FALSE;
    len = ft_strlen(arg);
    if(ft_isalpha(arg[0]) || arg[0] == '_')
        first_character = TRUE;
    i = 1;
    while(arg[i])
    {
        if(ft_isdigit(arg[i]) || ft_isalpha(arg[i]) || arg[i] == '_')
            other_character = TRUE;
        i++;
    }
    if(first_character && other_character && len > 1)
        return (TRUE);
    else if (first_character && len == 1)
        return (TRUE);
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
