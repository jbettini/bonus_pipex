/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:31:56 by jbettini          #+#    #+#             */
/*   Updated: 2021/10/19 12:56:52 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int tofind)
{
	int	i;

	i = ft_strlen(str);
	if (tofind == 0 || !str)
		return ((char *)str + ft_strlen(str));
	while (i != -1)
	{
		if (str[i] == (char)tofind)
			return ((char *)str + i);
		i--;
	}
	return (0);
}
