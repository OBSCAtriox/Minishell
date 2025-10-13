/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:33:52 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/01 20:11:25 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;

	if (*little == '\0')
		return ((char *)big);
	a = 0;
	while (big[a] != '\0' && a < len)
	{
		b = 0;
		while ((a + b) < len && big[a + b] == little[b] && little[b] != '\0')
			b++;
		if (little[b] == '\0')
			return ((char *)&big[a]);
		a++;
	}
	return (NULL);
}

/*int   main(void)
{
        char    str[] = "ola, bom boem dia";
        char    str1[] = "boe";
        int     a = 11;

        printf("%s", ft_strnstr(str, str1, a));
        return (0);
}*/
