/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:24:33 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/18 20:24:59 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_ptr(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}

static size_t	read_buffer(int fd, char **rest, char **buffer)
{
	size_t	nbytes;
	char	*tmprest;

	nbytes = 1;
	while (!(ft_strchr(*rest, '\n')) && nbytes)
	{
		nbytes = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[nbytes] = '\0';
		tmprest = *rest;
		*rest = ft_strjoin(*rest, *buffer);
		free_ptr(tmprest);
	}
	free_ptr(*buffer);
	return (nbytes);
}

static char	*set_lines(char **rest, char **line)
{
	size_t	lenrest;
	char	*tmprest;

	lenrest = 0;
	tmprest = *rest;
	while (((*rest)[lenrest] != '\0') && ((*rest)[lenrest] != '\n'))
		lenrest++;
	if (ft_strchr(*rest, '\n'))
	{
		*line = ft_substr(*rest, 0, lenrest + 1);
		*rest = ft_strdup(*rest + lenrest + 1);
	}
	else
	{
		*line = ft_strdup(tmprest);
		*rest = NULL;
	}
	free_ptr(tmprest);
	return (*line);
}

char	*get_next_line(int fd)
{
	size_t		nbytes;
	char		*line;
	char		*buffer;
	static char	*rest[MAX_FD];

	if ((BUFFER_SIZE > 0) && (fd >= 0))
	{
		buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return (NULL);
		if (read(fd, buffer, 0) < 0)
			return (free_ptr(buffer));
		if (!rest[fd])
			rest[fd] = ft_strdup("");
		nbytes = read_buffer(fd, &rest[fd], &buffer);
		set_lines(&rest[fd], &line);
		if ((nbytes == 0) && (*line == '\0'))
			return (free_ptr(line));
		return (line);
	}
	return (NULL);
}
