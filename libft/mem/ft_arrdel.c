/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 22:13:22 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 22:50:02 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Free a char * tab
** assume a NULL pointer has been allocated at the end
*/

#include "libft.h"

static void	del_loop(char **arr)
{
	if (*arr)
		del_loop(arr + 1);
	ft_memdel((void *)arr);
}

void	ft_arrdel(char ***arr)
{
	if (*arr)
		del_loop(*arr);
	ft_memdel((void *)arr);
}
