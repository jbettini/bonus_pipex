/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:26:14 by jbettini          #+#    #+#             */
/*   Updated: 2021/10/20 20:53:15 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pt, int value, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)pt)[i] = (unsigned char)value;
		i++;
	}
	return (pt);
}
