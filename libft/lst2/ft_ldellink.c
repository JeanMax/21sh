/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldellink.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 23:55:52 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:34:42 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** retire un élément 'n' de la liste, mais ne le supprime pas!
** l'élément 'n-1' pointera sur l'élément 'n+1'
*/

#include "libft.h"

void	ft_ldellink(t_lst *link)
{
	if (!link)
		return ;
	if (link->prev != NULL)
		link->prev->next = link->next;
	if (link->next != NULL)
		link->next->prev = link->prev;
	link->prev = NULL;
	link->next = NULL;
}
