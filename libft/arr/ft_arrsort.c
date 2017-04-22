/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 01:45:46 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/16 01:46:58 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sort an array using shell_sort (based on arr->cmp)
*/

#include "libft.h"

void			ft_arrsort(t_arr *arr)
{
	ft_shellsort(arr->ptr, arr->length, arr->sizeof_element, arr->cmp);
}
