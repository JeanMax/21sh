/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 17:02:22 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:42:20 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Echange la position de deux élements dans la liste
*/

#include "libft.h"

void	ft_lswap(t_lst *link1, t_lst *link2)
{
	t_lst	*target;
	t_lst	*swap;

	if (!link1->prev)
	{
		swap = link2;
		link2 = link1;
		link1 = swap;
	}
	if (link1->prev != link2)
		target = link1->prev;
	else
		target = link1;
	ft_ldellink(link1);
	ft_lrplc(link2, link1);
	ft_linser(&target, link2);
}
