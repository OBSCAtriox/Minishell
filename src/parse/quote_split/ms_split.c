#include "../../../includes/minishell.h"

static void ver_pos(int i, int st, char *li, t_quote_split **head, t_quote_split **tail)
{
	if (i > st)
		create_spl_list(head, tail,
			ft_substr(li, st, i - st), NONE);
}

static t_quote_type	ver_type(char c)
{
	if (c == '"')
		return (DOUBLE);
	else if (c == '\'')
		return (SINGLE);
	else
		return (NONE);
}

t_quote_split	*ms_split(char *li)
{
	t_split_var	v;

	init_split_vars(&v);
	while (li[v.i])
	{
		if (v.ty == NONE && ft_strchr("\"\'", li[v.i]))
		{
			if (v.i > v.st)
				create_spl_list(&v.head, &v.tail, ft_substr(li, v.st, (v.i
							- v.st)), v.ty);
			v.ty = ver_type(li[v.i]);
			v.st = v.i + 1;
		}
		else if (v.ty != NONE && ver_type(li[v.i]) == v.ty)
		{
			create_spl_list(&v.head, &v.tail,
				ft_substr(li, v.st, v.i - v.st), v.ty);
			v.ty = NONE;
			v.st = v.i + 1;
		}
		v.i++;
	}
	ver_pos(v.i, v.st, li, &v.head, &v.tail);
	return(v.head);
}
