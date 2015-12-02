/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 22:22:22 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/29 01:53:44 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the address of a node found using the cmp function
*/

#include "libft.h"

t_bst   **ft_bstfind(t_bst **root, t_bst *node, \
					 int (*cmp)(const void *a, const void *b, size_t n))
{
	int		ret;
	int		min;

	if (!(*root))
		return (root);
	min = ft_min((int)(*root)->content_size, (int)node->content_size);
	if (!(ret = cmp((*root)->content, node->content, (size_t)min)))
	{
		min = (int)node->content_size - (int)(*root)->content_size;
		if ((*root)->content_size == node->content_size)
			return (ft_bstfind(ret < 0 ? &(*root)->left : &(*root)->right, node, cmp));
		else
			return (ft_bstfind(ret < 0 ? &(*root)->left : &(*root)->right, node, cmp));
	}


	return (ft_bstfind(ret < 0 ? &(*root)->left : &(*root)->right, node, cmp));
}
