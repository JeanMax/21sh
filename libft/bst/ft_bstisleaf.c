/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstisleaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:39:45 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:39:34 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Return TRUE is the node is a leaf (left and right NULL), otherwise FALSE
*/

#include "libft.h"

t_bool		ft_bstisleaf(t_bst *node)
{
	if (!node)
		return (FALSE);
	return (node->right == NULL && node->left == NULL ? TRUE : FALSE);
}
