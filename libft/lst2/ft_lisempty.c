/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lisempty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 03:24:38 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:25:53 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** renvoie 1 si la liste est vide, 0 si elle contient au moins un élément.
*/

#include "libft.h"

t_bool		ft_lisempty(t_lst *link)
{
	return (link ? FALSE : TRUE);
}
