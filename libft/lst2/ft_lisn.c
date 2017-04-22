/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lisn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 23:47:29 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:28:58 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the position of the link in the list (first = 1)
** 0 is returned if fail
*/

#include "libft.h"

size_t			ft_lisn(t_lst *alst, t_lst *link)
{
	size_t	i;

	if (!alst || !link)
		return (0);
	if (alst == link)
		return (1);
	i = 2;
	while (alst->next && alst->next != link)
	{
		alst = alst->next;
		i++;
	}
	if (alst->next != link)
		return (0);
	return (i);
}
