/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isspaces_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:57 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/12 18:38:37 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_words(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ms_isspaces(str[i]) && (i == 0 || ms_isspaces(str[i - 1])))
			count += 1;
		i++;
	}
	return (count);
}

static int	str_size(char *str, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (ms_isspaces(str[i]))
			break ;
		i++;
	}
	return (i - start);
}

static int	make_arr(char *str, char **arr)
{
	size_t	i;
	size_t	y;
	size_t	len;

	i = 0;
	y = 0;
	while (str[i])
	{
		if (!ms_isspaces(str[i]) && (i == 0 || ms_isspaces(str[i - 1])))
		{
			len = str_size(str, i);
			arr[y] = ft_substr(str, i, len);
			if (!arr[y])
			{
				arr[y] = NULL;
				return (0);
			}
			y++;
			i += len;
		}
		else
			i++;
	}
	arr[y] = NULL;
	return (1);
}

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

char	**isspace_split(char *str)
{
	char	**arr;
	size_t	count;

	if (!str)
		return (NULL);
	count = count_words(str);
	if (count >= (SIZE_MAX / sizeof(char *)) - 1)
		return (NULL);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!make_arr(str, arr))
	{
		free_split(arr);
		return (NULL);
	}
	return (arr);
}
