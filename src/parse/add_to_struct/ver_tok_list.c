# include "../../../includes/minishell.h"

int     count_words(t_tokens *t)
{
    int count;

    count = 0;
    while(t)
    {
        if (t->type == WORD)
            count++;
        t = t->next;
    }
    return (count);
}

void num_redir_alloc(t_tokens *tmp)
{
    int count;
    int i;

    i = 0;
    while(tmp->next && ms()->cmdv[i])
    {
        count = 0;
        while (tmp->type != PPIPE && tmp->type != WORD)
        {
            if (tmp->type == PR_HDOC || tmp->type == PR_IN
                || tmp->type == PR_OUT || tmp->type == PR_APP)
                count++;
            tmp = tmp->next;
        }
        if (count != 0)
            redir_arr_malloc(count, i);
        i++;
    }
}

void    add_to_struct(t_tokens *t)
{
    t_vars v;

    init_s_var(&v);
    if (cmd_finder())
            ms()->cmdv[v.y]->argv[][]
    while (t)
    {
        
    }
}