/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:16:56 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/27 21:32:53 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	size_t		feedback;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		feedback = build_line(buffer, &line, fd);
		if (feedback == 0)
			break ;
		if (feedback == 2)
			return (NULL);
		if (newline(buffer))
		{
			found_rest(buffer);
			break ;
		}
		buffer[0] = '\0';
	}
	if (line && *line)
		return (line);
	free(line);
	return (NULL);
}

/*int	main(void)
{
	int		fd;
	char	*read;

	fd = open("arquivo.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("%s\n", "ABERTURA DO ARQUIVO FALHOU!");
		return (1);
	}
	read = get_next_line(fd);
	printf("%s", read);
	free(read);
	read = get_next_line(fd);
	printf("%s", read);
	free(read);
	read = get_next_line(fd);
	printf("%s", read);
	free(read);
	close(fd);
	return (0);
}*/
