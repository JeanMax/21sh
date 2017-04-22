/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 03:35:27 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:30:18 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Return a pointer to the link at index n, otherwise NULL if the list
** contains less than n links. (The first element's index is one)
** alst must be a pointer to the first link of the list.
*/

#include "libft.h"

t_list	*ft_lstat(t_list *alst, size_t n)
{
	if (!alst || !n)
		return (NULL);
	while (n-- && alst->next != NULL)
		alst = alst->next;
	return (alst);
}
