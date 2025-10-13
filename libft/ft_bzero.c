/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:46:17 by thde-sou          #+#    #+#             */
/*   Updated: 2025/04/15 20:21:53 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			a;
	unsigned char	*us;

	us = s;
	a = 0;
	while (a < n)
	{
		us[a] = 0;
		a++;
	}
}

/*int     main(void)
{
        int     a;
        char    str1[10] = "123456789";
        char    str2[10] = "123456789";

        bzero(str1, 4);
        ft_bzero(str2, 4);
        a = 0;
        while (a < 10)
        {
                printf("%d ", str1[a]);
                a++;
        }
        a = 0;
        printf("\n");
        while (a < 10)
        {
                printf("%d ", str2[a]);
                a++;
        }
        return (0);
}*/
