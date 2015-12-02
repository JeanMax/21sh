/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lisfirst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 04:32:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:27:26 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Retourne 1 si l'élément courant est le premier élément de la liste, 0 sinon.
*/

#include "libft.h"

t_bool	ft_lisfirst(t_lst *link)
{
	return (link->prev ? FALSE: TRUE);
}
