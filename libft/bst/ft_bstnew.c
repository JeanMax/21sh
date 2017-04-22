/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:23:57 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/18 15:45:38 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocate (with malloc(3)) a new node. If it fails, NULL is returned.
*/

#include "libft.h"
#include <stdlib.h>

t_bst	*ft_bstnew(void *content, size_t content_size)
{
	t_bst	*new;

	if (!(new = ft_memalloc(sizeof(t_bst))))
		return (NULL);
	if (content)
	{
		new->content_size = content_size;
		ft_memcpy(&new->content, &content, content_size);
	}
	new->height = 1;
	return (new);
}
