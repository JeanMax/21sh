/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:19:53 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/11 23:18:07 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The atoi() function converts the initial portion of the string  pointed
** to by nptr to int.
** If the string cannot be converted into a number, atoi returns 0.
** If the string represents a numeric value greater/lower than INT_MAX/MIN,
** INT_MAX/MIN will be returned
*/

#include "libft.h"

int				ft_atoi(char *str)
{
	t_bool	negative;
	long	ret;

	while (ft_isspace(*str))
		str++;
	negative = *str == '-' ? TRUE : FALSE;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str == '0')
		str++;
	ret = 0;
	while (*str && ft_isdigit(*str) && ret < INT_MAX)
		ret = ret * 10 + *(str++) - '0';
	if (negative)
		return (ret > INT_MAX ? INT_MIN : (int)-ret);
	else
		return (ret > INT_MAX ? INT_MAX : (int)ret);
}
