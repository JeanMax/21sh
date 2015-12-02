/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 16:47:50 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 19:52:12 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** compare two ints
*/

#include "libft.h"

int		ft_intcmp(const void *i1, const void *i2, size_t n)
{
	const int *swap1;
	const int *swap2;

	if (i1 != i2 && n)
	{
		swap1 = (const int *)i1;
		swap2 = (const int *)i2;
		n /= sizeof(int); 
		while (n--)
		{
			if (*swap1 != *swap2)
				return (*swap1 - *swap2);
			swap1++;
			swap2++;
		}
	}
	return (0);
}
