/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstinorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 21:25:32 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 21:36:10 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** apply a function to each nodes, inorder
*/

#include "libft.h"

void	ft_bstinorder(t_bst *root, void (*f)(t_bst *node))
{
	if (!root)
		return ;
	ft_bstinorder(root->left, f);
	f(root);
	ft_bstinorder(root->right, f);
}
