/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_cmd_list_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:45:00 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/25 19:45:00 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>

static int	is_dot_entry(const char *name)
{
	if (!name || name[0] != '.')
		return (FALSE);
	if (name[1] == '\0')
		return (TRUE);
	if (name[1] == '.' && name[2] == '\0')
		return (TRUE);
	return (FALSE);
}

static int	add_entry_cmd(const char *dir, const char *name, t_cmd_list *list)
{
	char	*full;
	int		ok;

	full = join3((char *)dir, BAR, (char *)name);
	if (!full)
		return (FALSE);
	ok = (!is_dir(full) && access(full, X_OK) == 0);
	free(full);
	if (!ok)
		return (TRUE);
	return (cmd_list_add(list, name));
}

static int	add_dir_cmds(const char *dir, t_cmd_list *list)
{
	DIR				*dp;
	struct dirent	*entry;

	dp = opendir(dir);
	if (!dp)
		return (TRUE);
	entry = readdir(dp);
	while (entry)
	{
		if (!is_dot_entry(entry->d_name))
		{
			if (!add_entry_cmd(dir, entry->d_name, list))
				return (closedir(dp), FALSE);
		}
		entry = readdir(dp);
	}
	closedir(dp);
	return (TRUE);
}

int	add_path_cmds(char *path, t_cmd_list *list)
{
	char	**dirs;
	int		i;

	if (!path)
		return (TRUE);
	dirs = ft_split(path, ':');
	free(path);
	if (!dirs)
		return (FALSE);
	i = 0;
	while (dirs[i])
	{
		if (!add_dir_cmds(dirs[i], list))
			return (free_doble_pointer(dirs), FALSE);
		i++;
	}
	free_doble_pointer(dirs);
	return (TRUE);
}
