/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:18:47 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/01 16:42:29 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	strlen;

	a = 0;
	strlen = ft_strlen(src);
	if (size == 0)
		return (strlen);
	while (a < size - 1 && src[a] != '\0')
	{
		dst[a] = src[a];
		a++;
	}
	dst[a] = '\0';
	return (strlen);
}

/*int     main(void)
{
	char    str[] = "banana";
        char    str1[10];
        int     z = 6;

        size_t  res = ft_strlcpy(str1, str, z);
        printf("%s\n", str1);
        printf("%zu\n", res);
        return (0);
}*/
