/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:17:25 by thde-sou          #+#    #+#             */
/*   Updated: 2025/08/27 22:20:39 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Encontra o que sobra depois do \n
Atualiza o buffer para concatenar com alinha e formar uma nova linha */
void	found_rest(char *buffer)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (buffer[a] && buffer[a] != '\n')
		a++;
	if (buffer[a] == '\n')
		a++;
	while (buffer[a])
		buffer[b++] = buffer[a++];
	buffer[b] = '\0';
}

/* Junta o buffer com a linha, limitando-se ao \n */
char	*ft_strjoin_modified(char *s1, char const *s2)
{
	char	*res;
	size_t	a;
	size_t	b;
	size_t	len1;
	size_t	len2;

	a = 0;
	b = 0;
	len1 = ft_strlen_modified(s1);
	len2 = ft_strlen_modified(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (free(s1), NULL);
	while (a < len1)
		res[b++] = s1[a++];
	a = 0;
	while (a < len2)
	{
		res[b++] = s2[a];
		if (s2[a++] == '\n')
			break ;
	}
	res[b] = '\0';
	free(s1);
	return (res);
}

/* Conta o tamanho do buffer e da linha para formar o malloc corretamente */
size_t	ft_strlen_modified(char const *s)
{
	size_t	a;

	a = 0;
	if (!s)
		return (0);
	while (s[a] && s[a] != '\n')
		a++;
	if (s[a] == '\n')
		a++;
	return (a);
}

/* Função encontra o \n (quebra de linha) */
int	newline(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

/* Função auxiliar do get_next_line */
/* Forma a nova linha e retorna erros */
/* Menor que zero. Erros de leitura ou alocação falhou */
/* Retorna 0 se o arquivo estiver vazio ou fim do arquivo */
int	build_line(char *buffer, char **line, int fd)
{
	ssize_t	bytes;

	if (*buffer == '\0')
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(*line), 2);
		if (bytes == 0)
			return (0);
		buffer[bytes] = '\0';
	}
	*line = ft_strjoin_modified(*line, buffer);
	if (!*line)
		return (2);
	return (1);
}
