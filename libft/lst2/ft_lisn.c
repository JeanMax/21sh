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
** retourne la position de l'élément dans la liste (premier = 1)
** 0 est retourné en cas d'echec
*/

#include "libft.h"

size_t			ft_lisn(t_lst *alst, t_lst *link)
{
	size_t	i;

	if (!alst || !link)
		return (FALSE);
	if (alst == link)
		return (1);
	i = 2;
	while (alst->next && alst->next != link)
	{
		alst = alst->next;
		i++;
	}
	if (alst->next != link)
		return (FALSE);
	return (i);
}
