/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 03:39:12 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 14:19:22 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** errors handling
** first arg is a flag including enums e_error (cf .h) (ex: E_OPEN | E_NOEXIT)
** second arg is an optionnal error message
*/

#include "flex_shell.h"
#include <stdlib.h>

t_bool fail(const char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	return (FALSE);
}

t_bool failn(const char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
	return (FALSE);
}

/*
** I'm pretty sure there is another way...
*/

static int		get_index(t_uint flag)
{
	int		index;

	index = 0;
	while ((flag /= 2))
		index++;
	return (index - 1);
}

void			error(t_uint flag, char *msg)
{
	const char	*error[] = {
		"21sh: command not found: ",
		"21sh: no such file or directory: ",
		"21sh: can't make file: ",
		"Pipe failed. Try Again...",
		"Fork failed. Try Again...",
		"Too many arguments.",
		"$PATH missing from env.",
		"This is not a tty.",
		"Getattr failed. Try Again...",
		"Setattr failed. Try Again...",
		"$TERM missing from env."
	};

	if (msg)
	{
		fail(error[get_index(flag & (t_uint)~E_NOEXIT)]);
		failn(msg);
	}
	else
		failn(error[get_index(flag & (t_uint)~E_NOEXIT)]);
	if (!(flag & E_NOEXIT))
		exit(EXIT_FAILURE);
}
