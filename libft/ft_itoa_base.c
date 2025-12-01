/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:09:34 by thde-sou          #+#    #+#             */
/*   Updated: 2025/07/18 05:39:12 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	repeat_char_base(const char *base)
{
	size_t	a;
	size_t	b;

	a = 0;
	while (base[a])
	{
		if (base[a] == '+' || base[a] == '-' || base[a] < 32 || base[a] > 126)
			return (0);
		b = a + 1;
		while (base[b])
		{
			if (base[a] == base[b])
				return (0);
			b++;
		}
		a++;
	}
	return (1);
}

static char	*convertion(unsigned long n, const char *base, size_t len)
{
	char	*result;
	char	buffer[33];
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (n > 0)
	{
		buffer[a] = base[n % len];
		n /= len;
		a++;
	}
	result = malloc(a + 1);
	if (!result)
		return (NULL);
	while (--a >= 0)
	{
		result[b] = buffer[a];
		b++;
	}
	result[b] = '\0';
	return (result);
}

static char	*if_zero(void)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa_base(unsigned long n, const char *base)
{
	unsigned long	base_len;
	char			*nbr;

	base_len = 0;
	if (!base)
		return (NULL);
	if (!repeat_char_base(base))
		return (NULL);
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (NULL);
	if (n == 0)
		return (if_zero());
	nbr = convertion(n, base, base_len);
	if (!nbr)
		return (NULL);
	return (nbr);
}

/*int	main(void)
{
	char	*str;
	int		num;

	num = 56f;
	str = ft_itoa_base(num, "0123456789");
	if (!str)
		return (0);
	printf("%s\n", str);
	free(str);
	return (0);
}*/
