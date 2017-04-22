/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldelone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 02:21:02 by mcanal            #+#    #+#             */
/*   Updated: 2016/04/03 11:47:24 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free the link's content using 'del' function, then free the link itself
** and set it to NULL
*/

#include "libft.h"

void			ft_ldelone(t_lst **alst, void (*del)(void*, size_t))
{
	if (!alst || !*alst)
		return ;
	if (del)
		del((*alst)->content, (*alst)->content_size);
	ft_memdel((void **)alst);
}
