/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 00:14:10 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 21:20:56 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

//alias setenv... won't check if to_add is well formated
//should be used with to_add = "SMURF=ETTE"
//to_add will be strdup'ed
static char		**arr_add(char **arr, char *to_add)
{
	char		**cpy;
	size_t		i;

	if (*(cpy = arr_find(arr, to_add)))
	{
		ft_memdel((void *)cpy);
		*cpy = ft_strdup(to_add);
		return (arr);
	}
	i = 0;
	while (arr[i])
		i++;
	cpy = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (arr[i])
	{
		cpy[i] = arr[i];
		i++;
	}
	cpy[i++] = ft_strdup(to_add);
	cpy[i] = NULL;
	ft_memdel((void *)&arr);
	return (cpy);
}

void			set_env(char *to_set)
{
	t_env		*e;

	e = get_env_struct();
	e->envp = arr_add(e->envp, to_set);
	if (!ft_strncmp("PATH", to_set, 4))
		update_bin(TRUE);
}
