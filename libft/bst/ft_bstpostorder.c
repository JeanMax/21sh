/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstpostorder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 21:25:32 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 22:19:00 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** apply a function to each nodes, postorder
*/

#include "libft.h"

void	ft_bstpostorder(t_bst *root, void (*f)(t_bst *node))
{
	if (!root)
		return ;
	ft_bstpostorder(root->left, f);
	ft_bstpostorder(root->right, f);
	f(root);
}
