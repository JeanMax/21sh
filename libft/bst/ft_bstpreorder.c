/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstpreorder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 21:25:32 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 21:35:51 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** apply a function to each nodes, preorder
*/

#include "libft.h"

void	ft_bstpreorder(t_bst *root, void (*f)(t_bst *node))
{
	if (!root)
		return ;
	f(root);
	ft_bstpreorder(root->left, f);
	ft_bstpreorder(root->right, f);
}
