/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 20:31:11 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 20:35:20 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the greatest element of the tree
*/

#include "libft.h"

t_bst	*ft_bstmax(t_bst *node)
{
	return (node->right ? ft_bstmax(node->right) : node);
}
