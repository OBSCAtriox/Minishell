#include "../../../includes/minishell.h"

void    update_argv(char **argv)
{
    int i;

    if(!argv || !argv[0])
        return;
    i = 0;
    add_fallback_var(argv[0]);
    free(argv[0]);
    while (argv[i + 1])
    {
        argv[i] = argv[i + 1];
        i++;
    }
    argv[i] = NULL;
}

void    add_fallback_var(char *arg)
{
    char **vetor;
    char *name;
    int size;
    int i;

    vetor = NULL;
    size = size_vetor(tc()->fallback_vars);
    copy_vetor(&vetor, tc()->fallback_vars);
    free_doble_pointer(tc()->fallback_vars);
    tc()->fallback_vars = malloc(sizeof(char *) * (size + 2));
    if(!tc()->fallback_vars)
        return;
    i = 0;
    copy_vetor(&tc()->fallback_vars, vetor);
    while(tc()->fallback_vars[i])
        i++;
    name = get_name_var(arg);
    tc()->fallback_vars[i++] = ft_strdup(name);
    tc()->fallback_vars[i] = NULL;
    free(name);
    free_doble_pointer(vetor);
}

static int aux_copy_vetor(char ***dest)
{
    if (!*dest)
    {
        *dest = malloc(sizeof(char *) * 1);
        if (!*dest)
            return (FALSE);
    }
    (*dest)[0] = NULL;
    return (TRUE);
}

int    copy_vetor(char ***dest, char **src)
{
    int i;

    if (!src)
        return (aux_copy_vetor(dest));
    if(!*dest)
    {
        *dest = malloc(sizeof(char *) * (size_vetor(src) + 1));
        if(!*dest)
            return (FALSE);
    }
    i = 0;
    while (src[i])
    {
        (*dest)[i] = get_name_var(src[i]);
        if(!(*dest)[i])
            return (free_vetor_failed(*dest, i), FALSE);
        i++;
    }
    (*dest)[i] = NULL;
    return (TRUE);
}

void    remove_vars_fallback(void)
{
    int i;

    i = 0;
    if(!tc()->fallback_vars)
        return;
    while(tc()->fallback_vars[i])
    {
        aux_unset(tc()->fallback_vars, i);
        i++;
    }
    free_doble_pointer(tc()->fallback_vars);
    tc()->fallback_vars = NULL;
}
