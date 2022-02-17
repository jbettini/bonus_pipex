/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:03:59 by jbettini          #+#    #+#             */
/*   Updated: 2021/10/18 18:38:06 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dstlen;

	dstlen = ft_strlen(dest);
	if (n > ft_strlen(dest) + ft_strlen(src) + 1)
	{
		ft_strcat(dest, src);
		return (ft_strlen(dest));
	}
	else
	{
		if (n >= ft_strlen(dest) + 1)
			ft_strncat(dest, src, n - ft_strlen(dest) - 1);
		else
			return (ft_strlen(src) + n);
		return (ft_strlen(src) + dstlen);
	}
}
