#include "../../includes/minishell.h"

int size_vetor(char **vetor)
{
    int i;

    i = 0;
    while(vetor[i])
        i++;
    return (i);
}

void    free_vetor_failed(char **vetor, int i)
{
    int j;

    if(!vetor)
        return ;
    j = 0;
    while(j < i)
    {
        free(vetor[j]);
        j++;
    }
    free(vetor);
}

int find_variable(char *name)
{
    char **env;
    int i;
    int len;

    env = te()->envp;
    i = 0;
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

void    free_doble_pointer(char **p)
{
    int i;

    if(!p)
        return ;
    i = 0;
    while(p[i])
    {
        free(p[i]);
        i++;
    }
    free(p);
}