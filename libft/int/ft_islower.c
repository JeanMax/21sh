/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 17:55:45 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/29 00:04:52 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** checks for a lower-case character.
*/

#include "libft.h"

int		ft_islower(int c)
{
	return (c >= 97 && c <= 122);
}