/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:30:30 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/05 23:55:10 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (len <= ft_strlen(s1))
		return (NULL);
	res = malloc(len);
	if (!res)
		return (NULL);
	ft_memmove(res, s1, ft_strlen(s1));
	res[ft_strlen(s1)] = '\0';
	ft_strlcat((char *)res, s2, len);
	return (res);
}

/*int     main(void)
{
        size_t  a = 0;
        char    *s1 = "abc";
        char    *s2 = "DEFF";
        char    *res;

        res = ft_strjoin(s1, s2);
        printf("Tamanho res: %zu\n", ft_strlen(res));
        while (a < ft_strlen(res) + 1)
        {
                printf("%d ", res[a]);
                a++;
        }
		free(res);
        return (0);
}*/
