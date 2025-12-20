/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:07:28 by thde-sou          #+#    #+#             */
/*   Updated: 2025/12/20 14:54:47 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *nptr)
{
	int	sign;
	long long	res;
	int	a;

	sign = 1;
	res = 0;
	a = 0;
	while ((nptr[a] >= 9 && nptr[a] <= 13) || nptr[a] == 32)
		a++;
	if (nptr[a] == '+' || nptr[a] == '-')
	{
		if (nptr[a] == '-')
			sign *= -1;
		a++;
	}
	while (nptr[a] >= '0' && nptr[a] <= '9')
	{
		res = res * 10 + (nptr[a] - '0');
		a++;
	}
	return (res * sign);
}

/*int     main(void)
{
        char    *str = " +123b6";

        printf("%d vs %d", atoi(str), ft_atoi(str));
        return (0);
}*/
