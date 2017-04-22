/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 21:07:51 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/12 19:24:50 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the address of a node found using the cmp function
** (search from a value)
*/

#include "libft.h"

t_bst	**ft_bstsearch(t_bst **root, void *content, size_t content_size, \
						t_cmp *cmp)
{
	t_bst	node;

	node.content = content;
	node.content_size = content_size;
	node.left = NULL;
	node.right = NULL;
	node.height = 1;
	return (ft_bstfind(root, &node, cmp));
}
