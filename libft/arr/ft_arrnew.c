/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 21:40:22 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/24 23:16:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** alloc and init a new t_arr
*/

#include "libft.h"

t_arr		*ft_arrnew(size_t length, size_t sizeof_element)
{
	t_arr	*new;

	new = (t_arr *)ft_memalloc(sizeof(t_arr));
	new->sizeof_element = sizeof_element ? sizeof_element : sizeof(void *);
	new->cpy = ft_memcpy;
	new->cmp = ft_memcmp;
	new->alloc_len = (length + 1) * sizeof_element;
	new->alloc_len = new->alloc_len + 32 - (new->alloc_len % 32);
	new->ptr = ft_memalloc(new->alloc_len);
	return (new);
}
