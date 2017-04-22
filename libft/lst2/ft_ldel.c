/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 02:24:42 by mcanal            #+#    #+#             */
/*   Updated: 2016/04/03 11:47:20 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free the link's content using 'del' function, free the link itself
** and set it to NULL. Same for all the successors
*/

#include "libft.h"

void			ft_ldel(t_lst **alst, void (*del)(void *, size_t))
{
	if (!alst || !*alst)
		return ;
	ft_ldel(&((*alst)->next), del);
	ft_ldelone(alst, del);
}
