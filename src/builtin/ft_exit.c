/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:42:30 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/13 17:41:23 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exit builtin
*/

#include "builtin.h"
#include <stdlib.h>

static int		do_exit(int status)
{
	ft_putendl("exit");
	finit_cursor();
	ft_hdel(&get_env_struct()->bin_table);
	exit(status);
}

void			ft_exit(char **av)
{
	int	ac;

	ac = 0;
	while (av[ac])
		ac++;
	if (ac == 1)
		do_exit(EXIT_SUCCESS);
	else if (ac == 2)
	{
		ac = 0;
		av++;
		while ((*av)[ac] && ft_isdigit((*av)[ac]))
			ac++;
		if ((*av)[ac])
			failn(ft_isdigit(**av) ? \
					"exit: Badly formed number." : "exit: Expression Syntax.");
		else
			do_exit(ft_atoi(*av));
	}
	else
		failn("exit: Expression Syntax.");
}
