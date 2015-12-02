/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 20:29:51 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 20:35:23 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the lowest element of the tree
*/

#include "libft.h"

t_bst	*ft_bstmin(t_bst *node)
{
	return (node->left ? ft_bstmin(node->left) : node);
}
