/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 22:11:05 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 22:18:33 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Return a copy of a string array.
*/

#include "libft.h"
#include <stdlib.h>

char			**ft_arrdup(char **arr)
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
