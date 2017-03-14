/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 22:38:08 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/22 23:01:06 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** eecho builtin
*/

#include "builtin.h"

void			ft_echo(char **av)
{
	t_bool	eol;

	eol = TRUE;
	++av;
	while (*av && **av == '-')
	{
		if (!ft_strcmp(*av, "-n"))
			eol = FALSE;
		else
			break ;
		av++;
	}
	while (*av)
	{
		ft_putstr(*av);
		if (*(av + 1))
			ft_putstr(" ");
		av++;
	}
	if (eol)
		ft_putendl("");
}
