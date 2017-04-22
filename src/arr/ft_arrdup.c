/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 22:11:05 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:53:09 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Return a copy of a string array.
*/

#include "arr.h"
#include <stdlib.h>

char			**ft_arr_dup(char **arr)
{
	char		**cpy;
	size_t		i;

	i = 0;
	while (arr[i])
		i++;
	cpy = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (arr[i])
	{
		cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
