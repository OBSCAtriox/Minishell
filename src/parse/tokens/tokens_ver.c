#include "../../../includes/minishell.h"

char *ver_expand_h(t_quote_split *h)
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

char    **expand_then_split(t_quote_split *h, t_tokens *t)
{
    t_quote_split *head;
    char *expanded;
    char **words;

    head = h;
    expand_quotes(h, t);
    expanded = ver_expand_h(head);
    if (!expanded)
        return (printf("here"), NULL);
    words = isspace_split(expanded);
    free(expanded);
    return (words);
}

void replace_tok_with_words(t_tokens *tok, char **words)
{
    t_tokens *cur;
    t_tokens *next;
    int i;
    if (!words || !words[0])
        return ;
    free(tok->value);
    tok->value = ft_strdup(words[0]);
    cur = tok;
    i = 1;
    while (words[i])
    {
        next = new_tok(ft_strdup(words[i]), tok->type);
        next->next = cur->next;
        if (cur->next)
            cur->next->prev = next;
        cur->next = next;
        next->prev = cur;
        cur = next;
        i++;
    }
}

void	ver_to_expand(t_tokens **t_head)
{
    t_tokens *t;
    t_quote_split   *h;
    char **words;
    char *expanded;

    t = *t_head;
	while (t)
	{
        h = ms_split(t->value);
        if (is_assignment(t->value))
        {
            expand_quotes(h, t);
            expanded = ver_expand_h(h);
            free(t->value);
            t->value = expanded;
        }
        else
        {
            words = expand_then_split(h, t);
            ver_to_expand_helper2(t, words);
        }
        free_split_list(&h);
        t = t->next;
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
