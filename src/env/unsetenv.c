/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 00:10:45 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:37:58 by mc               ###   ########.fr       */
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
	ft_arr_delone(e->envp, *arr_find(e->envp, to_unset));
	if (!ft_strncmp("PATH", to_unset, 4))
		update_bin(TRUE);
}
