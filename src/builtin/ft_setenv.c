/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:40:39 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 01:25:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** setenv builtin
*/

#include "flex_shell.h"

void			ft_setenv(char **av)
{
	if (!*(++av))
		print_env(get_env_struct()->envp);
	while (*av)
	{
		if (!syntax_error(*av))
			set_env(*av);
		else
		{
			fail("setenv: '");
			fail(*av);
			failn("': not a valid identifier.");
		}
		av++;
	}
}
