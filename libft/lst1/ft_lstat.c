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
** Retourne un pointeur sur l'élément à l'indice n, ou NULL si la liste
** contient moins de n élément(s).     (le premier élément a pour indice 0)
** **alst doit contenir l'adresse d’un pointeur sur le premier élément.
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
