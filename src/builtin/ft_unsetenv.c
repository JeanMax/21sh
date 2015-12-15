/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:41:27 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 20:46:10 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** unsetenv builtin
*/

#include "builtin.h"

void			ft_unsetenv(char **av)
{
	if (!*(++av))
		failn("unsetenv: Too few arguments.");
	while (*av)
	{
		if (get_env(*av))
			unset_env(*av);
		else
		{
			fail("unsetenv: '");
			fail(*av);
			failn("' not found.");
		}
		av++;
	}
}
