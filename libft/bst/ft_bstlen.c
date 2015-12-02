/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:49:30 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 16:04:01 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the number of nodes in the tree
*/

#include "libft.h"

size_t	ft_bstlen(t_bst *root)
{
	if (!root)
		return (0);
	return (1 + ft_bstlen(root->left) + ft_bstlen(root->right));
}
