/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstrotright.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 00:22:39 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:48:12 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** right rotate tree
**      y                            x
**     / \     Right Rotation       / \
**    x   c   – – – – – – – >      a   y
**   / \      < - - - - - - -     /     \
**  a   b      Left Rotation     b       c
*/

#include "libft.h"

t_bst	*ft_bstrotright(t_bst *y)
{
	t_bst	*x;
	t_bst	*b;

	x = y->left;
	b = x->right;
	x->right = y;
	y->left = b;
	return (x);
}
