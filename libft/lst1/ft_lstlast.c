/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 03:58:41 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:31:20 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** retourne un pointeur sur le dernier élément de la liste
*/

#include "libft.h"

t_list			*ft_lstlast(t_list *link)
{
	if (!link)
		return (NULL);
	while (link->next)
		link = link->next;
	return (link);
}
