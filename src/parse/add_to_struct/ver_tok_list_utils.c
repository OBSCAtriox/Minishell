#include "../../../includes/minishell.h"

int cmd_finder()
{
    if (ps()->tok->type == WORD)
        return (1);
    return (0);
}

void    redir_arr_malloc(int size, int i)
{
    ms()->cmdv[i]->redir = malloc(sizeof(t_redir) * size);
    if (!ms()->cmdv[i]->redir)
        free_all(MALLOC_FAIL, 1);
}

void    add_cmd_array(t_tokens *t)
{
    while (t || t->type != PPIPE)
    {
        if (t->type == WORD && t->prev->type != WORD
            && t->type != PPIPE)
            ft_strdup(t->value)
    }
}

void    malloc_ms_argv(t_tokens *t, int *i, int *y)
{
    int count;
    int tmp;

    tmp = 0;
    count = 0;
    while (tmp <= *i)
        t = t->next;
    while (t || t->type != PPIPE)
    {
        if (t->type == WORD && t->prev->type != WORD 
            && t->prev->type != PPIPE)
            count++;
        t = t->next;
    }
    ms()->cmdv[*y]->argv = malloc(sizeof(char *) * (count + 1));
    if (ms()->cmdv[*y]->argv)
        free_all(MALLOC_FAIL, 1);
}
