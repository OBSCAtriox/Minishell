/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:28:41 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/02 15:23:14 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmenb, size_t size)
{
	void	*arr;
	size_t	bytes;

	if (size != 0 && SIZE_MAX / size < nmenb)
		return (NULL);
	bytes = nmenb * size;
	arr = malloc(bytes);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, bytes);
	return (arr);
}

/*int     main(void)
{
	int     a = 0;
        int     z = 4;
        char     *arr = ft_calloc(z, sizeof(int));
        
        while (a < z)
        {       
                if (arr != NULL)
                        printf("%d", arr[a]);
                a++;
        }
        return (0);
}*/
