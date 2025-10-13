/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 00:23:05 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/04 18:52:22 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	if (write(fd, &c, 1) == -1)
		return ;
}

/*int     main(void)
{
        int     fd = 1;
        char    c = 'a';

        ft_putchar_fd(c, fd);
        printf("\n");
        return (0);
}*/
