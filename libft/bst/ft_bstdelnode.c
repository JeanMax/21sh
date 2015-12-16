/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:38:13 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 20:54:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** remove an element from the tree, then free it
*/

#include "libft.h"

void			ft_bstdel(t_bst **node)
{
	t_bst	*tmp;

	if (!(*node)->left)
	{
		tmp = *node;
		*node = (*node)->right;
		ft_bstfree(&tmp);
	}
	else if (!(*node)->right)
	{
		tmp = *node;
		*node = (*node)->left;
		ft_bstfree(&tmp);
	}
	else
	{
		tmp = ft_bstmax((*node)->left);
		ft_swap(&(*node)->content, &tmp->content, sizeof(void *));
		ft_swap(&(*node)->content_size, &tmp->content_size, sizeof(size_t));
		ft_bstdel(&tmp);
	}
}
