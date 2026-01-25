/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:45:00 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/25 19:45:00 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*cmd_generator(const char *text, int state)
{
	static size_t	len;
	static int		idx;
	static char		**cmds;

	if (state == 0)
	{
		free_doble_pointer(cmds);
		cmds = build_cmd_list();
		idx = 0;
		len = ft_strlen(text);
	}
	while (cmds && cmds[idx])
	{
		if (ft_strncmp(cmds[idx], text, len) == 0)
			return (ft_strdup(cmds[idx++]));
		idx++;
	}
	free_doble_pointer(cmds);
	cmds = NULL;
	return (NULL);
}

static char	**minishell_completion(const char *text, int start, int end)
{
	(void)end;
	if (start != 0)
		return (NULL);
	rl_attempted_completion_over = 1;
	return (rl_completion_matches(text, cmd_generator));
}

void	init_readline_completion(void)
{
	rl_attempted_completion_function = minishell_completion;
	rl_bind_key('\t', rl_complete);
}
