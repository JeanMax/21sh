/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfirst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 03:58:41 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:32:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** retourne un pointeur sur le premier élément de la liste
*/

#include "libft.h"

t_lst			*ft_lfirst(t_lst *link)
{
	if (!link)
		return (NULL);
	while (link->prev)
		link = link->prev;
	return (link);
}
