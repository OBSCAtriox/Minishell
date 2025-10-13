/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:35:26 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/03 03:18:33 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t					a;
	unsigned char			*u_dest;
	const unsigned char		*u_src;

	u_dest = (unsigned char *) dest;
	u_src = (const unsigned char *) src;
	a = 0;
	while (a < n)
	{
		u_dest[a] = u_src[a];
		a++;
	}
	return (dest);
}

/*int     main(void)
{
        int     origem[] = {1,2,3,4,5,6};
        int     destino1[6];
        int     destino2[6];
        int     size = 5;
        int     a;

        memcpy(destino1, origem, size * sizeof(int));
        ft_memcpy(destino2, origem, size * sizeof(int));
        a = 0;
        while (a < size)
        {
                printf("%d", destino1[a]);
                a++;
        }
        a = 0;
        printf("\n");
        while (a < size)
        {
                printf("%d", destino2[a]);
                a++;
        }
        return (0);
}*/
