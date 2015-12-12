/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 22:22:22 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/12 21:08:45 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the address of a node found using the cmp function
** (search from a node)
*/

#include "libft.h"

t_bst	**ft_bstfind(t_bst **root, t_bst *node, \
						int (*cmp)(const void *a, const void *b))
{
	int		ret;

	if (!(*root) || !(ret = cmp(*root, node)))
		return (root);
	return (ft_bstfind(ret < 0 ? &(*root)->left : &(*root)->right, node, cmp));
}
