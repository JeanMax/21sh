/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstgetbalance.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 00:17:42 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:47:46 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** check if a tree is balanced (0 if yes)
*/

#include "libft.h"

int		ft_bstgetbalance(t_bst *node)
{
	return ((int)ft_bstheight(node->left) - (int)ft_bstheight(node->right));
}
