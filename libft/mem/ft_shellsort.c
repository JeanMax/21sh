/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shellsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 23:16:44 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:36:57 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sort an array (using shell sort)
** length = length of the array
** n = sizeof(*array)
*/

#include "libft.h"

void		ft_shellsort(void *arr, size_t length, size_t n,
							int (*cmp)(const void *a, const void *b))
{
	const size_t	gaps[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0 };
	unsigned char	swap[n];
	size_t			i;
	int				j;
	int				ngap;

	ngap = -1;
	while ((i = gaps[++ngap]))
		while (i < length)
		{
			ft_memcpy(swap, ((char *)arr) + (i * n), n);
			j = (int)i - (int)gaps[ngap];
			while (j >= 0 && cmp(((char *)arr) + ((size_t)j * n), swap) > 0)
			{
				ft_memcpy(((char *)arr) + (((size_t)j + gaps[ngap]) * n), \
							((char *)arr) + ((size_t)j * n), n);
				j -= gaps[ngap];
			}
			ft_memcpy(((char *)arr) + (((size_t)j + gaps[ngap]) * n), swap, n);
			i++;
		}
}
