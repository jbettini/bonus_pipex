/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:27:01 by jbettini          #+#    #+#             */
/*   Updated: 2021/10/21 16:37:18 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isep(char s, char c)
{
	if (s == c)
		return (1);
	else
		return (0);
}

static size_t	word(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	w;

	j = 0;
	i = 0;
	w = 0;
	while (s[i] && s[j])
	{
		i = j;
		while (isep(s[i], c) && s[i])
			i++;
		j = i;
		while (!isep(s[j], c) && s[j])
			j++;
		if (j > i)
			w++;
	}
	return (w);
}

static int	alloc_char(size_t len, size_t index, char **str)
{
	str[index] = malloc(sizeof(char) * len + 1);
	if (!str[index])
		return (0);
	return (1);
}

static char	**wordalloc(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	w;

	w = 0;
	j = 0;
	i = 0;
	str = malloc(sizeof(char *) * word(s, c) + 1);
	if (!str)
		return (NULL);
	while (s[i] && s[j])
	{
		i = j;
		while (isep(s[i], c) && s[i])
			i++;
		j = i;
		while (!isep(s[j], c) && s[j])
			j++;
		if (j > i)
			if (!(alloc_char(j - i, w, str)))
				return (NULL);
		w++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	w;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	w = 0;
	str = wordalloc(s, c);
	if (!str)
		return (NULL);
	while (j < word(s, c))
	{
		w = 0;
		while (isep(s[i], c) && s[i])
			i++;
		while (!isep(s[i], c) && s[i])
			str[j][w++] = s[i++];
		str[j][w] = 0;
		j++;
	}
	str[j] = 0;
	return (str);
}
