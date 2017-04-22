/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:50:06 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/29 14:40:36 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Assign (with malloc (3)) and turns(returns) a "fresh" character string
** ended with one '\0 ' representing the integer n given in parameter.
** The negative numbers must be managed. If the allocation fails,
** the function return NULL.
*/

#include "libft.h"

static size_t	length(int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = length(n);
	if (n < 0)
	{
		n = -n;
		len++;
		if (!(str = ft_strnew(len)))
			return (NULL);
		*str = '-';
	}
	else if (!(str = ft_strnew(len)))
		return (NULL);
	str[--len] = (char)(n % 10 + '0');
	while (n /= 10)
		str[--len] = (char)(n % 10 + '0');
	return (str);
}
