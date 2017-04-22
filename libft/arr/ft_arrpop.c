/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 21:35:03 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/24 23:17:56 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pop an element from a t_arr
** the right side of the array will be moved consequently
** negative index allowed! (-1 == end)
*/

#include "libft.h"

void		*ft_arrpop(t_arr *arr, int index)
{
	t_uchar	*at_index;
	void	*ret;

	if (!arr->length)
		return (NULL);
	if (index < 0)
		index += (int)arr->length;
	if (index < 0 || index >= (int)arr->length)
		index = (int)arr->length - 1;
	at_index = (t_uchar *)arr->ptr + ((size_t)index * arr->sizeof_element);
	ft_memcpy(&ret, (void *)&at_index, \
				(size_t)ft_min((int)arr->sizeof_element, (int)sizeof(void *)));
	ft_memmove((void *)at_index, (void *)(at_index + arr->sizeof_element), \
				(arr->length - (size_t)index) * arr->sizeof_element);
	arr->length -= 1;
	return (ret);
}
