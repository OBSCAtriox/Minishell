#include "../../../includes/minishell.h"

static void	init_tok_split_list(t_per_cmd_tok **head, t_per_cmd_tok **tail,
		t_tokens **t, t_tokens **p, t_tokens *tok)
{
	*head = NULL;
	*tail = NULL;
	*t = tok;
	*p = NULL;
}

static t_per_cmd_tok	*new_cmd_list(t_tokens *tok_slice)
{
	t_per_cmd_tok	*new;

	if (!tok_slice)
		return NULL;
	new = malloc(sizeof(t_per_cmd_tok));
	if (!new)
		free_all(MALLOC_FAIL, 1);
	new->cmdt = tok_slice;
	new->next = NULL;
	return (new);
}

static void	add_list_to_list(t_per_cmd_tok **head, t_per_cmd_tok **tail,
		t_tokens *tok)
{
	t_per_cmd_tok	*new;

	new = new_cmd_list(tok);
	if (!new)
		free_all(MALLOC_FAIL, 1);
	if (!*head)
	{
		(*head) = new;
		(*tail) = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

t_per_cmd_tok	*tok_split(t_tokens *t)
{
	t_per_cmd_tok	*head;
	t_per_cmd_tok	*tail;
	t_tokens		*start;
	t_tokens		*prev;

	init_tok_split_list(&head, &tail, &start, &prev, t);
	while (t)
	{
		if (t->type == PPIPE)
		{
			if (prev)
				prev->next = NULL;
			add_list_to_list(&head, &tail, start);
			start = t->next;
		}
		prev = t;
		t = t->next;
	}
	if (start)
		add_list_to_list(&head, &tail, start);
	return (head);
}
