#include "../../../includes/minishell.h"

int find_next_min(char **env, int *printed)
{
    int i;
    int min_i;

    min_i = -1;
    i = 0;
    while(env[i])
    {
        if(!printed[i])
        {
            if(min_i == -1 || ft_strcmp_var(env[i], env[min_i]) < 0)
                min_i = i;
        }
        i++;
    }
    return (min_i);
}

int ft_strcmp_var(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=')
    {
        if(s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void    print_export_line(char *env)
{
    int i;

    i = 0;
    write(1, "declare -x ", 11);
    while (env[i] && env[i] != '=')
        write(1, &env[i++], 1);
    if(env[i] == '=')
    {
        write(1, "=\"", 2);
        i++;
        while (env[i])
            write(1, &env[i++], 1);
        write(1, "\"", 1);
    }
    write(1, "\n", 1);
}

int has_equal(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if(arg[i] == '=')
            return (TRUE);
        i++;
    }
    return (FALSE);    
}
