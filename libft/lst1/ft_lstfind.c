/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 05:25:28 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 19:19:19 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** retourne l’adresse du premier élément dont la donnée est
** "égale" à la donnée de référence
*/

#include "libft.h"

t_list			**ft_lstfind(t_list **alst, void *data, \
							int (*cmp)(const void *a, const void *b, size_t n))
{
	if (!(*alst) || !cmp((*alst)->content, data, (*alst)->content_size))
		return (alst);
	return (ft_lstfind(&(*alst)->next, data, cmp));
}
