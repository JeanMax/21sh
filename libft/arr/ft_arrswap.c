/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 00:35:10 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/16 22:17:13 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** swap 2 elements of the array
** negative index allowed! (-1 == end)
*/

#include "libft.h"

void			ft_arrswap(t_arr *arr, int i, int j)
{
	void	*swap;

	if (i < 0)
		i += (int)arr->length;
	if (j < 0)
		j += (int)arr->length;
	if (i < 0 || j < 0 || i >= (int)arr->length || j >= (int)arr->length \
			|| i == j || arr->length < 2)
		return ;
	i *= (int)arr->sizeof_element;
	j *= (int)arr->sizeof_element;
	ft_memcpy(&swap, \
				(void *)((t_uchar *)arr->ptr + (size_t)i), \
				arr->sizeof_element);
	ft_memcpy((void *)((t_uchar *)arr->ptr + (size_t)i), \
				(void *)((t_uchar *)arr->ptr + (size_t)j), \
				arr->sizeof_element);
	ft_memcpy((void *)((t_uchar *)arr->ptr + (size_t)j), \
				&swap, \
				arr->sizeof_element);
}
