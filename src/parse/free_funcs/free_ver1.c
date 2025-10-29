#include "../../../includes/minishell.h"

void free_tokens()
{
	t_tokens *head;
	t_tokens *tmp;

	head = ps()->tok;
	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
	ps()->tok = NULL;
}

void	free_all(char *msg)
{
	if (ps()->tok)
		free_tokens();
	/* if (ms()->cmdv)
	{
	} */
	ps_error(msg);
}
