/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 04:25:32 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:29:41 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** retourne la taille de la liste
*/

#include "libft.h"

size_t	ft_llen(t_lst *alst)
{
	size_t	i;

	if (!alst)
		return (0);
	i = 1;
	while (alst->next)
	{
		alst = alst->next;
		i++;
	}
	return (i);
}
