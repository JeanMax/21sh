/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 18:59:32 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/19 00:33:24 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** insert a node in the tree (if the value isn't already there)
** return NULL if a node was actually added, if a node has been replaced
** his content will be returned (free...? it's up to you!)
*/

#include "libft.h"

void	*ft_bstadd(t_bst **root, void *content, size_t content_size, t_cmp *cmp)
{
	t_bst	**where;
	t_bst	*new;
	void	*ret;

	if (!*root)
		*root = ft_bstnew(content, content_size);
	else
	{
		new = ft_bstnew(content, content_size);
		if (!*(where = ft_bstfind(root, new, cmp)))
			*where = new;
		else
		{
			ret = new->content;
			ft_memdel((void *)&new);
			return (ret);
		}
	}
	return (NULL);
}
