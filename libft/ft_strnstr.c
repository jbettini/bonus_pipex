/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:42:56 by jbettini          #+#    #+#             */
/*   Updated: 2021/10/18 18:44:11 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (tofind[i] == 0)
		return ((char *)str);
	while (str[i] && i < n)
	{
		if (str[i] == tofind[j])
		{
			while (str[i + j] == tofind[j] && i + j < n)
			{
				if (tofind[j + 1] == '\0' )
					return ((char *)str + i);
				j++;
			}
		}
		j = 0;
		i++;
	}
	return (0);
}
