# include "../../../includes/minishell.h"

void    remove_empty_tokens(t_tokens **head)
{
    t_tokens *cur;
    t_tokens *next;

    cur = *head;
    while (cur)
    {
        next = cur->next;
        if (cur->type == WORD && cur->value && cur->value[0] == '\0'
            && !cur->quote && !(cur->prev && if_redir(cur->prev->type)))
        {
            if (cur->prev)
                cur->prev->next = cur->next;
            else
                *head = cur->next;
            if (cur->next)
                cur->next->prev = cur->prev;
            free(cur->value);
            free(cur);
        }
        cur = next;
    }
}

void    expand_quotes(t_quote_split *h, t_tokens *t)
{
    char *tmp;
    char *original;

    while (h)
    {
        if (h->type != SINGLE 
            && (!t->prev || t->prev->type != PR_HDOC))
        {
            original = h->str;
            tmp = expand_line(h->str);
            if(!tmp)
                return;
            if (original[0] == '$' && !ft_strcmp(tmp, original))
            {
                free(tmp);
                tmp = ft_strdup("\x1F");
            }
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
        if (words[0][0] == '\0')
            t->value = ft_strdup("");
        else
            t->value = ft_strdup(words[0]);
    }
    free_doble_pointer(words);
}
