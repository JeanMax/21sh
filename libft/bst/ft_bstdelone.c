/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:38:13 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/21 16:41:22 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** remove an element from the tree, then free it
*/

#include "libft.h"

static void		del_node(t_bst **node, t_del *del)
{
	del((*node)->content, (*node)->content_size);
	ft_memdel((void *)node);
}

void			ft_bstdelone(t_bst **node, t_del *del)
{
	t_bst	*tmp;
	t_bst	*parent;

	if (!(*node)->left)
	{
		tmp = *node;
		*node = (*node)->right;
		del_node(&tmp, del);
	}
	else if (!(*node)->right)
	{
		tmp = *node;
		*node = (*node)->left;
		del_node(&tmp, del);
	}
	else
	{
		tmp = (*node)->right;
		parent = NULL;
		while (tmp->left && (parent = tmp))
			tmp = tmp->left;
		ft_swap(&(*node)->content, &tmp->content, sizeof(void *));
		ft_swap(&(*node)->content_size, &tmp->content_size, sizeof(size_t));
		ft_bstdelone(parent ? &parent->left : &(*node)->right, del);
	}
}
