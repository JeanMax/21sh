/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 02:25:42 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:53:03 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free a string from a string array
** the right side of the array will be moved consequently
*/

#include "arr.h"

void		ft_arr_delone(char **arr, char *to_del)
{
	while (*arr && *arr != to_del)
		arr++;
	if (!*arr)
		return ;
	ft_memdel((void *)&to_del);
	while ((*arr = *(arr + 1)))
		arr++;
}
