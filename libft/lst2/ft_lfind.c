/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 04:58:45 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 19:19:29 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** retourne l’adresse du premier élément dont la donnée est
** "égale" à la donnée de référence
*/

#include "libft.h"

t_lst **ft_lfind(t_lst **alst, void *data, \
				int (*cmp)(const void *a, const void *b, size_t n))
{
	if (!(*alst) || !cmp((*alst)->content, data, (*alst)->content_size))
		return (alst);
	return (ft_lfind(&(*alst)->next, data, cmp));
}
