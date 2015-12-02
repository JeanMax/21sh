/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstislast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 04:32:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:28:13 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Retourne 1 si l'élément courant est le dernier élément de la liste, 0 sinon.
*/

#include "libft.h"

t_bool	ft_lstislast(t_list *link)
{
	return (link->next ? FALSE: TRUE);
}
