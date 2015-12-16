/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstisperfect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 00:14:09 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:48:47 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** check if a tree is balanced
*/

#include "libft.h"

t_bool	ft_bstisperfect(t_bst *root)
{
	return (root ? ft_bstheight(root->left) == ft_bstheight(root->right) && \
			ft_bstisperfect(root->left) && ft_bstisperfect(root->right) : TRUE);
}
