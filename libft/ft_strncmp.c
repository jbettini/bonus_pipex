/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:42:00 by jbettini          #+#    #+#             */
/*   Updated: 2021/10/18 18:42:27 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	n1;
	unsigned char	n2;

	i = 0;
	n1 = s1[i];
	n2 = s2[i];
	while ((s1[i] || s2[i]) && i < n)
	{
		n1 = s1[i];
		n2 = s2[i];
		if (n1 != n2)
			return (n1 - n2);
		i++;
	}
	return (0);
}
