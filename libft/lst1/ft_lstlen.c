/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 04:25:32 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:29:30 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the length of the list
*/

#include "libft.h"

size_t	ft_lstlen(t_list *alst)
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
