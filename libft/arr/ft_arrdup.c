/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 22:11:05 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/24 00:07:43 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return a deep copy of a t_arr (based on arr->cpy)
*/

#include "libft.h"

t_arr			*ft_arrdup(t_arr *arr)
{
	t_arr		*dup;
	t_uchar		*a_src;
	t_uchar		*a_dup;
	size_t		i;

	dup = ft_memalloc(sizeof(t_arr));
	ft_memcpy(dup, arr, sizeof(t_arr));
	dup->ptr = ft_memalloc(arr->alloc_len);
	a_src = (t_uchar *)arr->ptr;
	a_dup = (t_uchar *)dup->ptr;
	i = arr->length;
	while (i--)
	{
		arr->cpy((void *)a_dup, (void *)a_src, arr->sizeof_element);
		a_src += arr->sizeof_element;
		a_dup += arr->sizeof_element;
	}
	return (dup);
}
