/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:29:58 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/24 23:29:59 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*dup_or_err(const char *str)
{
	char	*dup;

	dup = ft_strdup(str);
	if (!dup)
		return (set_err(errno), NULL);
	return (dup);
}

static char	*shorten_home(char *cwd)
{
	char	*home;
	char	*short_cwd;
	size_t	home_len;

	home = expand_variable("HOME", te()->envp);
	if (!home)
		return (dup_or_err(cwd));
	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) == 0
		&& (cwd[home_len] == '/' || cwd[home_len] == '\0'))
	{
		if (cwd[home_len] == '\0')
			short_cwd = dup_or_err("~");
		else
			short_cwd = join3("~", cwd + home_len, NULL);
	}
	else
		short_cwd = dup_or_err(cwd);
	free(home);
	return (short_cwd);
}

static char	*get_cwd_fallback(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
		return (cwd);
	if (!te()->cwd)
		return (set_err(errno), NULL);
	return (dup_or_err(te()->cwd));
}

static char	*build_prompt_str(const char *short_cwd)
{
	char	*prompt;
	size_t	len;

	len = ft_strlen(RL_GREEN) + ft_strlen("T_shell ") + ft_strlen(RL_CYAN)
		+ ft_strlen(short_cwd) + ft_strlen(RL_WHITE)
		+ ft_strlen(" -") + ft_strlen("> ")
		+ ft_strlen(RL_RESET) + 1;
	prompt = ft_calloc(sizeof(char), len);
	if (!prompt)
		return (set_err(errno), NULL);
	ft_strlcat(prompt, RL_GREEN, len);
	ft_strlcat(prompt, "T_shell ", len);
	ft_strlcat(prompt, RL_CYAN, len);
	ft_strlcat(prompt, short_cwd, len);
	ft_strlcat(prompt, RL_WHITE, len);
	ft_strlcat(prompt, " -", len);
	ft_strlcat(prompt, "> ", len);
	ft_strlcat(prompt, RL_RESET, len);
	return (prompt);
}

char	*build_prompt(void)
{
	char	*cwd;
	char	*short_cwd;
	char	*prompt;

	cwd = get_cwd_fallback();
	if (!cwd)
		return (NULL);
	short_cwd = shorten_home(cwd);
	free(cwd);
	if (!short_cwd)
		return (NULL);
	prompt = build_prompt_str(short_cwd);
	free(short_cwd);
	return (prompt);
}
