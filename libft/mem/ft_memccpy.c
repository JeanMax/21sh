/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:38:44 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/05 21:38:58 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memccpy() function copies no more than n bytes from memory area src
** to memory area dest, stopping when the character c is found.
*/

#include "libft.h"

void			*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dswap;
	const char	*sswap;

	dswap = dest;
	sswap = src;
	while (n--)
	{
		if (*sswap == c)
		{
			*dswap++ = *sswap++;
			return (dswap);
		}
		*dswap++ = *sswap++;
	}
	return (NULL);
}
