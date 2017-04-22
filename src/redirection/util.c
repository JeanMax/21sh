/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:25:22 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:36:55 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** a couple functions used in the redirection part
*/

#include "redirection.h"

int				get_fd(char *s)
{
	int		fd;

	if (!s)
		return (-1);
	while (*s && !ft_isdigit(*s) && *s != '-')
		s++;
	if (!*s)
		return (-1);
	fd = ft_atoi(s);
	return (fcntl(fd, F_GETFD) ? -1 : fd);
}

void			do_redirect(char **cmd, enum e_replacement c, int o_flag, \
						void (*do_stuff_with_cmd_and_fd_now)(char **, int, int))
{
	int		fd_left;
	int		fd_right;
	char	**swap;
	char	*tmp;

	swap = cmd;
	while (*(++swap) && !(tmp = ft_strchr(*swap, c)))
		;
	if (*swap == tmp || (fd_left = get_fd(*swap)) == -1)
	{
		fd_left = c == R_INPUT ? STDIN_FILENO : STDOUT_FILENO;
		*tmp = 0;
	}
	if ((fd_right = open(*(++swap), o_flag, 0664)) == -1)
		error(E_OPEN | E_NOEXIT, *swap);
	if (*tmp || tmp == *(swap - 1))
	{
		tmp = *swap;
		ft_arr_delone(cmd, *(swap - 1));
		ft_arr_delone(cmd, tmp);
	}
	else
		ft_arr_delone(cmd, *swap);
	do_stuff_with_cmd_and_fd_now(cmd, fd_left, fd_right);
}
