/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:18:58 by thde-sou          #+#    #+#             */
/*   Updated: 2025/12/18 17:45:52 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	z_dst;
	size_t	z_src;
	size_t	z_sum;

	if(!dst || !src)
		return (0);
	z_dst = ft_strlen(dst);
	z_src = ft_strlen(src);
	z_sum = (z_dst + z_src);
	a = 0;
	if (size <= z_dst)
		return (z_src + size);
	while (src[a] != '\0' && z_dst + a < size - 1)
	{
		dst[z_dst + a] = src[a];
		a++;
	}
	dst[z_dst + a] = '\0';
	return (z_sum);
}

/*int     main(void)
{
        char    str1[10] = "1234";
        char    str2[] = "56";
        int     z = 3;
        size_t  res = ft_strlcat(str1, str2, z);

        printf("%s", str1);
        printf("\n%zu", res);
        return (0);
}*/
