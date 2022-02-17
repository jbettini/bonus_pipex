/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:31:37 by jbettini          #+#    #+#             */
/*   Updated: 2021/10/18 16:32:15 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*li;

	li = *alst;
	if (alst)
	{
		if (*alst)
		{
			while (li->next)
				li = li->next;
			li->next = new;
		}
		else
			*alst = new;
	}
}
