/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 16:41:47 by mcanal            #+#    #+#             */
/*   Updated: 2016/09/27 21:32:41 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env			*get_env_struct(void)
{
	static t_env	e = {NULL, NULL, 0};

	return (&e);
}

/*
** alias getenv... return the adress of the pointer to the begin of the smurf
** to_find = "SMURF"		->	"SMURF=ETTE"
** to_find = "SMURF=ETTE"	->	"SMURF=ETTE"
*/

char			**arr_find(char **arr, char *to_find)
{
	char	*s1;
	char	*s2;

	while (*arr)
	{
		s1 = *arr;
		s2 = to_find;
		while (*s1 && *s2 && *s1 != '=' && *s1 == *s2 && s1++ && s2++)
			;
		if (*s1 == '=' && (*s2 == '=' || !*s2))
			return (arr);
		arr++;
	}
	return (arr);
}

char			*get_env(char *to_get)
{
	return (*arr_find(get_env_struct()->envp, to_get));
}
