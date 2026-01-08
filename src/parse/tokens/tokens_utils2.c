# include "../../../includes/minishell.h"

void    expand_quotes(t_quote_split *h, t_tokens *t)
{
    char *tmp;

    while (h)
    {
        if (h->type != SINGLE 
            && (!t->prev || t->prev->type != PR_HDOC))
        {
            tmp = expand_line(h->str);
            free(h->str);
            h->str = tmp;
        }
        h = h->next;
    }
}

void    ver_to_expand_helper2(t_tokens *t, char **words)
{
    if (words && words[1])
        replace_tok_with_words(t, words);
    else if (words && words[0])
    {
        free(t->value);
        t->value = ft_strdup(words[0]);
    }
    free_doble_pointer(words);
}
