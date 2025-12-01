/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:20:26 by thde-sou          #+#    #+#             */
/*   Updated: 2025/04/15 19:42:40 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	long unsigned int	a;
	unsigned char		uc;

	uc = (unsigned char) c;
	a = 0;
	while (a < n)
	{
		((unsigned char *)s)[a] = uc;
		a++;
	}
	return (s);
}

/*int	main(void)
{
	int	a;
	char	str1[10] = "abcdefghi";
	char    str2[10] = "abcdefghi";

	a = 0;
	ft_memset(str1, 'a', 3);
	memset(str2, 'a', 3);
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
