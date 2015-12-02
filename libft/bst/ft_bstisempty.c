/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstisempty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:46:13 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:39:47 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** renvoie 1 si la liste est vide, 0 si elle contient au moins un élément.
*/

#include "libft.h"

t_bool		ft_bstisempty(t_bst *root)
{
	return (root ? FALSE : TRUE);
}
