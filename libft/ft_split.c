/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 05:01:11 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/05 23:49:33 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	size_t	a;
	int		count;

	if (!str)
		return (0);
	a = 0;
	count = 0;
	while (str[a] != '\0')
	{
		if ((a == 0 || str[a - 1] == c) && str[a] != c)
			count += 1;
		a++;
	}
	return (count);
}

static int	count_str(char const *s, char c, int start)
{
	int	a;

	a = start;
	while (s[a] != '\0')
	{
		if (s[a] == c)
			break ;
		a++;
	}
	return (a - start);
}

static int	make_split(char const *s, char **arr, char c)
{
	size_t	a;
	size_t	b;
	size_t	len;

	a = 0;
	b = 0;
	while (s[a] != '\0')
	{
		if ((a == 0 || s[a - 1] == c) && s[a] != c)
		{
			len = count_str(s, c, a);
			arr[b] = ft_substr(s, a, len);
			if (!arr[b])
			{
				arr[b] = NULL;
				return (0);
			}
			b++;
			a += len;
		}
		else
			a++;
	}
	arr[b] = NULL;
	return (1);
}

static void	free_all(char **arr)
{
	int	a;

	a = 0;
	while (arr[a])
	{
		if (arr[a])
			free(arr[a]);
		a++;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	if (count >= (SIZE_MAX / sizeof(char *)) - 1)
		return (NULL);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!make_split(s, arr, c))
	{
		free_all(arr);
		return (NULL);
	}
	return (arr);
}

/* int     main(void)
{
        int     a;
        int     b;
        char    *str = "aaaacbbbcddd";
        char    c = 'c';
        char    **arr = ft_split(str, c);

        a = 0;
        while (arr[a] != NULL)
        {
                printf("%s ", arr[a]);
                a++;
        }
        b = 0;
        while (arr[b])
                free(arr[b++]);
        free(arr);
        return (0);
} */