#include "../../../includes/minishell.h"

static char *ver_expand_h(t_quote_split *h)
{
    char *tmp;
    char *new_s;

    new_s = NULL;
    while (h)
    {
        if (!new_s)
            new_s = ft_strdup(h->str);
        else
        {
            tmp = new_s;
            new_s = ft_strjoin(new_s, h->str);
            free(tmp);
        }
        h = h->next;
    }
    return (new_s);
}
//adicionar verification para ver se he H DOC ou nao
void	ver_to_expand(t_tokens *t)
{
    t_quote_split   *h;
    char *exp_s;
    char *new_s;

	while (t)
	{
        ps()->sp = ms_split(t->value);
        h = ps()->sp;
        while (h)
        {
            if (h->type != SINGLE)
            {
                if (t->prev && t->prev->type != PR_HDOC)
                {
                    exp_s = expand_line(h->str);
                    free(h->str);
                    h->str = exp_s;
                }
            }
            h = h->next;
        }
        h = ps()->sp;
        new_s = ver_expand_h(h);
        free(t->value);
        t->value = new_s;
        t = t->next;
        free_split_list(&ps()->sp);
    }
}

void     verify_contain_quote(t_tokens *t)
{
    int i;
    while (t)
    {
        t->quote = 0;
        i = 0;
        while (t->value[i])
        {
            if (t->value[i] == '"' || t->value[i] == '\'')
            {
                t->quote = 1;
                break ;
            }
            i++;
        }
        t = t->next;
    }
}
