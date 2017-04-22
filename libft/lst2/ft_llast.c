/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 03:58:41 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:32:03 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return a pointer to the last link of the list
*/

#include "libft.h"

t_lst			*ft_llast(t_lst *link)
{
	if (!link)
		return (NULL);
	while (link->next)
		link = link->next;
	return (link);
}
