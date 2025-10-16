#include "../../../includes/minishell.h"

void    free_all(void)
{
    if(te()->envp)
        free_doble_pointer(te()->envp);
    if(te()->l_var)
        free_doble_pointer(te()->l_var);
    if(te()->oldpwd)
        free(te()->oldpwd);
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
