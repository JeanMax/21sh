/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 00:10:45 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 00:11:29 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flex_shell.h"

//alias unsetenv... accept a non existing pointer
//should be used with to_del = *arr_find(arr, KEY)
static void		arr_remove(char **arr, char *to_del)
{
	while (*arr && *arr != to_del)
		arr++;
	if (!*arr)
		return ;
	ft_memdel((void *)&to_del);
	while ((*arr = *(arr + 1)))
		arr++;
}

void			unset_env(char *to_unset)
{
	t_env		*e;

	e = get_env_struct();
	arr_remove(e->envp, *arr_find(e->envp, to_unset));
	if (!ft_strncmp("PATH", to_unset, 4))
		update_bin(TRUE);
}
