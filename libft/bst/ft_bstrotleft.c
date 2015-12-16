/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstrotleft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 00:22:36 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:48:19 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** left rotate tree
**      y                            x
**     / \     Right Rotation       / \
**    x   c   – – – – – – – >      a   y
**   / \      < - - - - - - -     /     \
**  a   b      Left Rotation     b       c
*/

#include "libft.h"

t_bst	*ft_bstrotleft(t_bst *x)
{
	t_bst	*y;
	t_bst	*b;

	y = x->right;
	b = y->left;
	y->left = x;
	x->right = b;
	return (x);
}
