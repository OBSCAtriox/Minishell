#include "../../../includes/minishell.h"

int	r_ver_start(const char *li)
{
	int	i;

	i = 0;
	while (li[i])
	{
		if (ms_isspaces(li[i]))
			i++;
		else
		{
			if (ft_strchr("<>", li[i]))
			{
				if (li[i] == '<' && li[i + 1] == '<')
					break ;
				return (0);
			}
			break ;
		}
	}
	return (1);
}

int	r_ver_end(const char *li)
{
	int	i;

	i = ft_strlen(li) - 1;
	while (li[i])
	{
		if (ms_isspaces(li[i]))
			i--;
		else
		{
			if (ft_strchr("<>", li[i]))
				return (0);
			break ;
		}
	}
	return (1);
}

int	r_ver(const char *li)
{
	bool	d_q;
	bool	s_q;

	d_q = false;
	s_q = false;
	if (!r_ver_start(li) || !r_ver_end(li) || !r_ver_after(d_q, s_q, li) 
		|| !r_ver_synt(d_q, s_q, li) || !r_ver_bef_aft_pipe(d_q, s_q, li))
		return(free_all(SYNT_ERR_R), 0);
	/* if (!r_ver_bef_aft_pipe(d_q, s_q, li))
		return (free_all("Debug 0\n"), 0);
	if (!r_ver_start(li))
		return (free_all("Debug 1\n"), 0);
	if (!r_ver_end(li))
		return (free_all("Debug 2\n"), 0);
	if (!r_ver_after(d_q, s_q, li))
		return (free_all("Debug 4\n"), 0);
	if (!r_ver_synt(d_q, s_q, li))
		return (free_all("Debug 5\n"), 0); */
	return (1);
}
