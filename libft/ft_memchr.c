/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:30:36 by thde-sou          #+#    #+#             */
/*   Updated: 2025/04/18 20:11:03 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	uc;
	unsigned char	*us;

	a = 0;
	us = (unsigned char *)s;
	uc = c;
	while (a < n)
	{
		if (us[a] == uc)
			return (&us[a]);
		a++;
	}
	return (NULL);
}

/*int     main(void)
{
        char    *str = "banana";
        char    c = 'n';
        int     d = 3;
        char    *prt1 = memchr(str, c, d);
        char    *prt2 = ft_memchr(str, c, d);

        printf("%s vs %s", prt1, prt2);
        return (0);
}*/
