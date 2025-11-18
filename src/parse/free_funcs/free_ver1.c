#include "../../../includes/minishell.h"

void free_tokens()
{
	t_tokens *head;
	t_tokens *tmp;

	head = ps()->tok;
	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
	ps()->tok = NULL;
}

void	free_split_list(t_quote_split **head)
{
	t_quote_split *tmp;

	while(*head)
	{
		tmp = (*head)->next;
		if ((*head)->str)
			free((*head)->str);
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}

void	free_all(char *msg, int i)
{
	if (ps()->tok)
		free_tokens();
	if (ps()->sp)
		free_split_list(&ps()->sp);
	/* if (ms()->cmdv)
	{
	} */
	ps_error(msg);
	if (i)
		exit(0);
}
