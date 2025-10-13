/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:17:35 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/02 17:24:14 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				a;
	unsigned char		*u_dest;
	const unsigned char	*u_src;

	u_dest = (unsigned char *) dest;
	u_src = (const unsigned char *) src;
	a = 0;
	if (u_dest > u_src)
	{
		while (n--)
			u_dest[n] = u_src[n];
	}
	else
	{
		while (a < n)
		{
			u_dest[a] = u_src[a];
			a++;
		}
	}
	return (dest);
}

/*int     main(void)
{
        int     str1[] = {1,2,3,4,5,6};
        int     str2[10];
        int     str3[10];
        int     z = 6;
        int     a = 0;

        memmove(str2, str1, z * sizeof(int));
        ft_memmove(str3, str1, z * sizeof(int));
        while (a < z)
        {
                printf("%d ", str2[a]); 
                a++;
        }
        printf("\n");
        a = 0;
        while (a < z)
        {
                printf("%d ", str3[a]); 
                a++;
        }
        return (0);
}*/
