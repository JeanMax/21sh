/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 20:39:57 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 20:51:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** swap the value of 2 elements
*/

#include "libft.h"

void	ft_swap(void *a, void *b, size_t n)
{
	char	tmp[n];

	ft_memcpy(tmp, b, n);
	ft_memcpy(b, a, n);
	ft_memcpy(a, tmp, n);
}
