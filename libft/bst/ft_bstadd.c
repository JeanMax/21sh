/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 18:59:32 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 18:10:45 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** insert a node in the tree (if the value isn't already there)
*/

#include "libft.h"

void	ft_bstadd(t_bst **root, void *content, size_t content_size, \
					int (*cmp)(const void *a, const void *b))
{
	t_bst	**where;
	t_bst	*new;

	if (!*root)
		*root = ft_bstnew(content, content_size);
	else
	{
		new = ft_bstnew(content, content_size);
		if (!*(where = ft_bstfind(root, new, cmp)))
			*where = new;
		else
			ft_bstfree(&new);
	}
}
