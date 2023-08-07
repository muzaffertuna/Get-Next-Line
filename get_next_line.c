/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:59:05 by mtoktas           #+#    #+#             */
/*   Updated: 2023/08/07 19:21:16 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_next(char *str)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	next = (char *)malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	if (!next)
		return (NULL);
	while (str[i])
		next[j++] = str[i++];
	next[j] = 0;
	free(str);
	return (next);
}

char	*ft_line(char *str)
{
	int		i;
	char	*line;

	if (!str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_read(char *str, int fd)
{
	int		f;
	int		i;
	char	*buf;

	i = 0;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (i < BUFFER_SIZE)
		buf[i++] = 0;
	if (!buf)
		return (NULL);
	f = 1;
	while (f > 0 && !ft_strchr(buf, '\n'))
	{
		f = read(fd, buf, BUFFER_SIZE);
		if (f == -1)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		buf[f] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read(str, fd);
	if (!str || !*str)
	{
		if(str)
			free(str);
		str = NULL;
		return (NULL);
	}
	line = ft_line(str);
	str = ft_next(str);
	return (line);
}
