/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 03:58:41 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/04 18:44:13 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Free a char * array
*/

#include "libft.h"

void	ft_freestab(char **arr)
{
	char	**swap;

	swap = arr;
	while (*arr)
		ft_memdel((void *)(arr++));
	ft_memdel((void *)(arr));
	ft_memdel((void *)&swap);
}
