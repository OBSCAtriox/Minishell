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
		{
			free(head->value);
			head->value = NULL;
		}
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

void	free_double_pchar(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i++] = NULL;
	}
	free(arr);
}

void	free_all(char *msg, int i)
{
	if (!ft_strcmp(MALLOC_FAIL, msg));
		te()->exit_code = 1;
	if (ps()->tok)
		free_tokens();
	if (ps()->sp)
		free_split_list(&ps()->sp);
	/* if (ms()->cmdv)
	{
	} */
	/* if (ps()->line)
		free(ps()->line); */
	if (ps()->line)
	{
		free(ps()->line);
		ps()->line = NULL;
	}
	ps_error(msg);
	if (i)
	{
		if (te()->envp)
			free_double_pchar(te()->envp);
		if (te()->l_var)
			free_doble_pointer(te()->l_var);
		if (te()->oldpwd)
			free(te()->oldpwd);
		return(clear_history(), exit(0), (void)(0));
	}
}
