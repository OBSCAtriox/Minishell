#include "../../../includes/minishell.h"

/* char *tok_unquote(const char *str)
{
	t_vars			v;
	t_quote_split	*h;
	char			*tmp;
	char			*ex_s;
	char			*new_v;

	init_s_var(&v);
	while (str[v.i])
	{
		quotes_ver(&v.d_q, &v.s_q, str[v.i]);
		if (str[v.i] == '"' && v.d_q)
	}
} */

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
                exp_s = expand_line(h->str);
                free(h->str);
                h->str = exp_s;
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
