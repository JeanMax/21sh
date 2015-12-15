/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:40:00 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 18:36:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** cd builtin
*/

#include "builtin.h"
#include <unistd.h>

static void	chdir_it(char *to)
{
	char	buf[PATH_SIZE];
	char	*tmp;

	if (chdir(to))
	{
		fail("cd: no such file or directory: ");
		failn(to);
	}
	else
	{
		tmp = ft_strjoin("OLDPWD=", get_env("PWD") + 4);
		set_env(tmp);
		ft_memdel((void *)&tmp);
		tmp = ft_strjoin("PWD=", getcwd(buf, PATH_SIZE));
		set_env(tmp);
		ft_memdel((void *)&tmp);
	}
}

static void	go_to(char *to)
{
	char		*tmp;

	if (*to != '/')
	{
		tmp = ft_strjoin(get_env("PWD") + 4, "/");
		to = ft_strjoin(tmp, to);
		chdir_it(to);
		ft_memdel((void *)&tmp);
		ft_memdel((void *)&to);
	}
	else
		chdir_it(to);
}

static void	minimal_env(void)
{
	char	buf[PATH_SIZE];
	char	*tmp;

	if (!get_env("PWD"))
	{
		tmp = ft_strjoin("PWD=", getcwd(buf, PATH_SIZE));
		set_env(tmp);
		ft_memdel((void *)&tmp);
	}
	if (!get_env("OLDPWD"))
	{
		tmp = ft_strjoin("OLDPWD=", getcwd(buf, PATH_SIZE));
		set_env(tmp);
		ft_memdel((void *)&tmp);
	}
	if (!get_env("HOME"))
	{
		tmp = ft_strjoin("HOME=", getcwd(buf, PATH_SIZE));
		set_env(tmp);
		ft_memdel((void *)&tmp);
	}
}

void		ft_cd(char **av)
{
	minimal_env();
	if (!*(++av))
		go_to(get_env("HOME") + 5);
	else if (!*(av + 1))
		ft_strcmp(*av, "-") ? go_to(*av) : go_to(get_env("OLDPWD") + 7);
	else
		failn("cd: Too many arguments.");
}
