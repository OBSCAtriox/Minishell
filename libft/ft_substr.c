/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:46:25 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/04 12:16:46 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	str_len;
	size_t	len_exit;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len_exit = str_len - start;
	else
		len_exit = len;
	if (len_exit + 1 <= len_exit)
		return (NULL);
	str = malloc(len_exit + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, len_exit + 1);
	return (str);
}

/*int     main(void)
{
        char    *str = "tripouille";
        int     start = 6;
        int     len = 3;
        size_t  a = 0;
        char    *prt = ft_substr(str, start, len);
        size_t  len_prt = ft_strlen(prt) + 1;

        printf("tamanho alocado: %zu\n", ft_strlen(prt) + 1);
        printf("tamanho da string: %zu\n", ft_strlen(str));
        while (a < len_prt)
        {
                printf("%d ", prt[a]);
                a++;
        }
        return (0);
}*/
