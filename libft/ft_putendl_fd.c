/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 00:55:36 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/04 17:00:47 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	a;

	if (fd < 0 || !s)
		return ;
	a = 0;
	while (s[a] != '\0')
	{
		if (write(fd, &s[a], 1) == -1)
			return ;
		a++;
	}
	if (write(fd, "\n", 1) == -1)
		return ;
}

/*int     main(void)
{
        char    str[] = "abcd";
        int     fd = 1;

        ft_putendl_fd(str, fd);
        return (0);
}*/
