/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 22:13:22 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:52:55 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Free a char * tab
** assume a NULL pointer has been allocated at the end
*/

#include "arr.h"

static void	del_loop(char **arr)
{
	if (*arr)
		del_loop(arr + 1);
	ft_memdel((void *)arr);
}

void		ft_arr_del(char ***arr)
{
	if (*arr)
		del_loop(*arr);
	ft_memdel((void *)arr);
}
