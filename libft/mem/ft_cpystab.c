/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpystab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 18:57:58 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/04 18:44:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Return a copy of a string array.
** If "val" isn't set to NULL, the function will add a string to the array
** with the "val" value.
*/

#include "libft.h"
#include <stdlib.h>

char			**ft_cpystab(char **arr, char *val)
{
	size_t		i;
	char		**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = malloc((i + (val ? 2 : 1)) * sizeof(char *));
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	if (val)
		new_arr[i] = ft_strdup(val);
	new_arr[i + (val ? 1 : 0)] = NULL;
	return (new_arr);
}
