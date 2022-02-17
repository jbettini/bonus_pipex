// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   get_next_line.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/10/30 21:39:00 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/17 12:04:04 by jbettini         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "libft.h"

// int	ft_chrgnl(char *str, int c)
// {
// 	size_t	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == (char)c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// static char	*rline(char *save, int fd)
// {
// 	int		ret;
// 	char	*buf;

// 	ret = 1;
// 	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buf)
// 		return (NULL);
// 	while (!ft_chrgnl(save, '\n') && ret != 0)
// 	{
// 		ret = read(fd, buf, BUFFER_SIZE);
// 		if (ret == -1)
// 		{
// 			free(buf);
// 			buf = 0;
// 			return (NULL);
// 		}
// 		buf[ret] = 0;
// 		save = ft_strjoin(save, buf);
// 	}
// 	free(buf);
// 	return (save);
// }

// static char	*makeline(char *save)
// {
// 	size_t	i;
// 	char	*line;

// 	i = 0;
// 	if (!save[i])
// 		return (NULL);
// 	while (save[i] && save[i] != '\n')
// 		i++;
// 	if (save[i] == '\n')
// 		line = malloc(sizeof(char) * i + 2);
// 	else
// 		line = malloc(sizeof(char) * i + 1);
// 	if (!line)
// 		return (NULL);
// 	i = -1;
// 	while (save[++i] && save[i] != '\n')
// 		line[i] = save[i];
// 	if (save[i] == '\n')
// 	{
// 		line[i] = save[i];
// 		i++;
// 	}
// 	line[i] = 0;
// 	return (line);
// }

// static char	*nextline(char *save)
// {
// 	char	*newsave;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (save[i] && save[i] != '\n')
// 		i++;
// 	if (save[i])
// 	{
// 		newsave = malloc(sizeof(char) * (ft_strlen(save) - i) + 1);
// 		if (!newsave)
// 			return (NULL);
// 		while (save[i])
// 			newsave[j++] = save[++i];
// 		newsave[j] = 0;
// 		free(save);
// 		return (newsave);
// 	}
// 	else
// 	{
// 		free(save);
// 		return (NULL);
// 	}
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	static char	*save;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	save = rline(save, fd);
// 	if (!save)
// 		return (NULL);
// 	line = makeline(save);
// 	save = nextline(save);
// 	return (line);
// }

char *ft_strjoin_fd(char *s1, char *s2)
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	result = NULL;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = 0;
	}
	result = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i++] = s2[j++];
	}
	result[i] = 0;
	free(s1);
	return (result);
}

char *get_line(int fd)
{
	int r;
	char *line;
	char *buffer;

	line = NULL;
	buffer = NULL;
	buffer = (char *)malloc(sizeof(char) * 2);
	while (1)
	{
		r = read(fd, buffer, 1);
		if (r == -1)
		{
			if (buffer)
				free(buffer);
			free(line);
			return NULL;
		}
		if (r == 0)
		{
			free(buffer);
			return (line);
		}
		buffer[1] = 0;
		if (buffer[0] == '\n')
		{
			line = ft_strjoin_fd(line, buffer);
			free(buffer);
			return (line);
		}
		line = ft_strjoin_fd(line, buffer);
	}
	free(buffer);
	return (line);
}


char *get_next_line(int fd)
{
	char *result;

	result = NULL;
	result = get_line(fd);
	return (result);
}
