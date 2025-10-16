#include "../../includes/minishell.h"

int size_vetor(char **vetor)
{
    int i;

    i = 0;
    if(!vetor)
        return (i);
    while(vetor[i])
        i++;
    return (i);
}

int find_variable(char *name, char **env)
{
    int i;
    int len;

    i = 0;
    if(!env)
        return (-1);
    while(env[i])
    {
        len = ft_strlen(name);
        if(ft_strncmp(env[i], name, len) == 0)
            return (i);
        i++;
    }
    return (-1);
}

char    *join3(char *s1, char *s2, char *s3)
{
    int len;
    char    *str;

    len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
    str = ft_calloc(sizeof(char), len);
    if(!str)
        return (NULL);
    ft_strlcat(str, s1, len);
    ft_strlcat(str, s2, len);
    ft_strlcat(str, s3, len);
    return (str);
}
