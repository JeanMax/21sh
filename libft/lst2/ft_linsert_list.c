/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linsert_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 00:30:59 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:44:31 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** insert a list src inside a list dst, (after dst link)
*/

#include "libft.h"

void	ft_linsert_list(t_lst *dst, t_lst *src)
{
	t_lst	*end;

	end = dst->next;
	dst->next = src;
	src->prev = dst;
	if (!end)
		return ;
	while (src->next)
		src = src->next;
	src->next = end;
	end->prev = src;
}
