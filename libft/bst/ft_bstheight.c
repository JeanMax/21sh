/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstheight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 23:40:56 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:51:16 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the height of the binary tree
*/

#include "libft.h"

size_t	ft_bstheight(t_bst *root)
{
	return (root ? 1 + (size_t)ft_max((int)ft_bstheight(root->left),
										(int)ft_bstheight(root->right)) : 0);
}
