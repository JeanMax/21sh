/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lclean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 04:42:41 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 20:53:33 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free the whole list
*/

#include "libft.h"

void	ft_lclean(t_lst **alst)
{
	t_lst	*next;

	if (!*alst)
		return ;
	next = (*alst)->next;
	ft_lfree(alst);
	ft_lclean(&next);
}
