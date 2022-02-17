/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:32:39 by jbettini          #+#    #+#             */
/*   Updated: 2021/10/19 12:56:05 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int tofind)
{
	size_t	i;

	i = 0;
	if (tofind == 0 || !str)
		return ((char *)str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (char)tofind)
			return ((char *)str + i);
		i++;
	}
	return (0);
}
