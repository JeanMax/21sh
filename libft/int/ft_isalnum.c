/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:23:09 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 23:58:23 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** checks for an alphanumeric character; it is equivalent to
** (isalpha(c) || isdigit(c)).
*/

#include "libft.h"

int		ft_isalnum(int i)
{
	return (ft_isalpha(i) || ft_isdigit(i));
}
