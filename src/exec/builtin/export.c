#include "../../../includes/minishell.h"

void    builtin_export(char **argv)
{
    int i;

    i = 1;
    if(!argv || !argv[1])
        return (print_export());
    while(argv[i])
    {
        if(is_valid_identifier(argv[i]))
        {
            if(aux_export(argv, i))
                te()->exit_code = 0;
            else
                te()->exit_code = 1;
        }
        else
        {
            write(2, "export: ", 8);
            print_error(argv[1], "not a valid identifier");
            te()->exit_code = 1;
        }
        i++;
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
        if(!name || !value)
            return ;
        env_set(name, value, te()->envp);
    }
}

int aux_export(char **argv, int i)
{
    char    *name;
    char    *value;

    name = get_name_var(argv[i]);
    value = get_value_var(argv[i]);
    if(!name || !value)
        return (FALSE);
    if(has_equal(argv[i]) && !value)
    {
        if(!env_set(name, "", te()->envp))
            return (FALSE);
    }
    else if(!has_equal(argv[i]) && !value)
        export_variable(name);
    else
    {
        if(!env_set(name, value, te()->envp))
            return (FALSE);
    }
    free(name);
    free(value);
    return (TRUE);
}
