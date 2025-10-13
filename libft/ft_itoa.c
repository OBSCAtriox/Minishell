/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:04:59 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/04 13:18:25 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_dig(long int num)
{
	int	a;

	a = 0;
	while (num != 0)
	{
		num /= 10;
		a++;
	}
	return (a);
}

static char	*convertion(long int num, size_t len, int n)
{
	char	*result;
	int		a;
	int		b;

	a = len - 1;
	if (len + 1 <= len)
		return (NULL);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		b = 1;
		result[0] = '-';
	}
	else
		b = 0;
	while (a >= b)
	{
		result[a] = num % 10 + '0';
		num = num / 10;
		a--;
	}
	result[len] = '\0';
	return (result);
}

static char	*if_zero(void)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long int	num;
	int			len_dig;
	char		*str;

	num = (long int)n;
	len_dig = 0;
	if (num == 0)
		return (if_zero());
	len_dig = count_dig(num);
	if (num < 0)
	{
		num = num * -1;
		len_dig += 1;
	}
	str = convertion(num, len_dig, n);
	if (str == NULL)
		return (NULL);
	return (str);
}

/*int     main(void)
{
        char    *str;
        int     num = 0;

        str = ft_itoa(num);
        printf("%s\n", str);
        return (0);
}*/
