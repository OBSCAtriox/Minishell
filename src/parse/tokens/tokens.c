#include "../../../includes/minishell.h"

void	create_token(t_tokens **head, t_tokens **tail, char *buffer, int buf_i)
{
	t_tokens	*tok;

	tok = malloc(sizeof(t_tokens));
	if (!tok)
		free_all(MALLOC_FAIL);
	buffer[buf_i] = '\0';
	tok->value = ft_strdup(buffer);
	if (!tok->value)
		free_all(MALLOC_FAIL);
	tok->type = WORD;
	tok->next = NULL;
	if (*head == NULL)
	{
		*head = tok;
		*tail = tok;
	}
	else
	{
		(*tail)->next = tok;
		*tail = tok;
	}
}

static void	add_token(t_tokens **head, t_tokens **tail, char *sym,
		t_token_type type)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		free_all(MALLOC_FAIL);
	new->value = ft_strdup(sym);
	if (!new->value)
		free_all(MALLOC_FAIL);
	new->type = type;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

static void	handle_symbols(t_tokens **head, t_tokens **tail, const char *li, int *i)
{
	if (li[*i] == '|')
		return (add_token(head, tail, "|", PPIPE), (*i)++, (void)(0));
	else if (li[*i] == '<')
	{
		if (li[*i + 1] == '<')
			return (add_token(head, tail, "<<", PR_HDOC), inc_i(i, 1), (void)(0));
		else
			return (add_token(head, tail, "<", PR_IN), inc_i(i, 0), (void)(0));
	}
	else if (li[*i] == '>')
	{
		if (li[*i + 1] == '>')
			return (add_token(head, tail, ">>", PR_APP), inc_i(i, 1), (void)(0));
		else
			return (add_token(head, tail, ">", PR_OUT), inc_i(i, 0), (void)(0));
	}
}

static void	token_help(t_tokens **head, t_tokens **tail, const char *li)
{
	char	buf[BUF_SIZE];
	int		i;
	int		buf_i;
	bool	d_quotes;
	bool	s_quotes;

	init_token(&i, &buf_i, &d_quotes, &s_quotes);
	while (li[i])
	{
		quotes_ver(&d_quotes, &s_quotes, li[i]);
		if (isspace(li[i]) && !d_quotes && !s_quotes)
		{
			buf_i_ver(head, tail, buf, &buf_i, true);
			i++;
		}
		else if ((ft_strchr("><|", li[i])) && !d_quotes && !s_quotes)
		{
			buf_i_ver(head, tail, buf, &buf_i, true);
			handle_symbols(head, tail, li, &i);
		}
		else
			buf[buf_i++] = li[i++];
	}
	buf_i_ver(head, tail, buf, &buf_i, false);
	ft_bzero(buf, ft_strlen(buf));
}

void	token_list(const char *li)
{
	t_tokens	*head;
	t_tokens	*tail;

	head = NULL;
	tail = NULL;
	token_help(&head, &tail, li);
	ps()->tok = head;
}
