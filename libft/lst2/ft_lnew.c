/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 22:07:36 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/18 15:22:06 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocate (with malloc(3)) a new link. If it fails, NULL is returned.
*/

#include "libft.h"

t_lst	*ft_lnew(void *content, size_t content_size)
{
	t_lst	*new;

	if (!(new = ft_memalloc(sizeof(t_lst))))
		return (NULL);
	if (content)
	{
		new->content_size = content_size;
		ft_memcpy(&new->content, &content, content_size);
	}
	return (new);
}
