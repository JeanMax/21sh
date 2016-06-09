/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 00:10:45 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/09 11:17:54 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** alias unsetenv... accept a non existing pointer
** should be used with to_del = *arr_find(arr, KEY)
*/

void			unset_env(char *to_unset)
{
	t_env		*e;

	e = get_env_struct();
	ft_arrdelone(e->envp, *arr_find(e->envp, to_unset));
	if (!ft_strncmp("PATH", to_unset, 4))
		update_bin(TRUE);
}
