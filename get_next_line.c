/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:51:43 by iriadyns          #+#    #+#             */
/*   Updated: 2024/10/27 16:25:09 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <fcntl.h>
// #include <stdio.h>
#include "get_next_line.h"

char	*ft_get_line(char *strread)
{
	int		i;
	char	*line;

	i = 0;
	if (!strread[i])
		return (NULL);
	while (strread[i] && strread[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (strread[i] && strread[i] != '\n')
	{
		line[i] = strread[i];
		i++;
	}
	if (strread[i] == '\n')
	{
		line[i] = strread[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_rest(char *strread)
{
	int		i;
	int		c;
	char	*rest;

	i = 0;
	while (strread[i] && strread[i] != '\n')
		i++;
	if (!strread[i])
	{
		free(strread);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(strread) - i + 1));
	if (!rest)
		return (NULL);
	i++;
	c = 0;
	while (strread[i])
		rest[c++] = strread[i++];
	rest[c] = '\0';
	free(strread);
	return (rest);
}

char	*ft_read(int fd, char *strread)
{
	char	*buff;
	int		readbytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	readbytes = 1;
	while (readbytes != 0)
	{
		readbytes = read(fd, buff, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(buff);
			free(strread);
			return (NULL);
		}
		buff[readbytes] = '\0';
		strread = ft_strjoin(strread, buff);
		if (ft_strchr(strread, '\n'))
			break ;
	}
	free(buff);
	return (strread);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*strread;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483648)
		return (NULL);
	strread = ft_read(fd, strread);
	if (!strread)
		return (NULL);
	line = ft_get_line(strread);
	strread = ft_rest(strread);
	return (line);
}

// int	main(void)
// {
// 	int	fd = open("test.txt", O_RDONLY);
// 	char *line;

// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	return (0);
// }

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line.h
// get_next_line_utils.c
