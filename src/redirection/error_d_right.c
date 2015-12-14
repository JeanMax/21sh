/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_d_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:48:44 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 01:58:21 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** append output (>>&) handler
** usage : "cmd >>& file"
*/

#include "flex_shell.h"

static void		check_error(char **cmd, char *pgm)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (ft_strcmp(">>&", cmd[i - 1]) && ft_strcmp(">>&", cmd[i]))
		{
			fail(pgm);
			if (!ft_strcmp("ls", pgm))
			{
				fail(": cannot access ");
			}
			else
				fail(": ");
			fail(cmd[i]);
			failn(": No such file or directory");
		}
		i++;
	}
}

static char		**check_cmd(char **cmd)
{
	int		i;
	int		j;
	int		ac;

	ac = 0;
	while (cmd[ac])
		ac++;
	i = 0;
	while (cmd[i] && ft_strcmp(">>&", cmd[i]))
		i++;
	check_error(&cmd[i], cmd[0]);
	j = ac - 1;
	while (cmd[j] && ft_strcmp(">>&", cmd[j]))
		j--;
	if (i == j)
		return (cmd);
	cmd[i + 1] = cmd[j + 1];
	i += 2;
	while (cmd[i])
	{
		cmd[i] = NULL;
		i++;
	}
	return (cmd);
}

static int		is_ambiguous(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], ">>&"))
		i++;
	if (!cmd[i])
		return (0);
	i++;
	while (cmd[i] && !ft_strchr(cmd[i], '>') && !ft_strchr(cmd[i], '<')\
			&& !ft_strchr(cmd[i], '|'))
		i++;
	if (cmd[i])
		return (1);
	return (0);
}

static void		handle_fd(int file_fd, char **cmd)
{
	int		err_fd;
	int		in_fd;

	in_fd = dup(1);
	err_fd = dup(2);
	dup2(file_fd, 1);
	dup2(file_fd, 2);
	launch_cmd(cmd);
	dup2(in_fd, 1);
	dup2(err_fd, 2);
	close(file_fd);
	close(err_fd);
	close(in_fd);
}

void			error_d_right(char **c)
{
	int		file_fd;
	int		i;

	c = is_ambiguous(c) ? c : check_cmd(c);
	i = 0;
	while (c[i] && ft_strcmp(c[i], ">>&"))
		i++;
	!c[i + 1] ? failn("Missing name for redirect.") : 0;
	!ft_strcmp(c[0], ">>&") && c[i + 1] ? failn("Invalid null command.") : 0;
	is_ambiguous(c) && ft_strcmp(c[0], ">>&") && c[i + 1] ?\
		failn("Ambiguous output redirect.") : 0;
	if (!c[i + 1] || !ft_strcmp(c[0], ">>&") || is_ambiguous(c))
		return ;
	if ((file_fd = open(c[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664)) < 0)
	{
		error(E_OPEN | E_NOEXIT, c[i + 1]);
		return ;
	}
	while (c[i])
		ft_memdel((void *)&c[i++]);
	handle_fd(file_fd, c);
}
