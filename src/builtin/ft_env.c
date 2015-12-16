/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:42:03 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 00:32:42 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** env builtin
*/

#include "builtin.h"
#include <stdlib.h>

void			print_env(char **envp)
{
	if (envp)
		while (*envp)
			ft_putendl(*(envp++));
}

t_bool			syntax_error(char *s)
{
	if (*s == '=')
		return (FALSE);
	while (*s && ft_isalnum(*s))
		s++;
	return (*s != '=');
}

static void		do_stuff(char **av, t_env *e)
{
	e->bin_root = NULL;
	if (!ft_strcmp(*av, "-i"))
	{
		e->envp = (char **)malloc(sizeof(char *));
		*e->envp = NULL;
		av++;
	}
	else
		e->envp = ft_arrdup(e->envp);
	while (*av && !syntax_error(*av))
		set_env(*(av++));
	if (*av)
	{
		update_bin(TRUE);
		exec_cmd(av);
	}
	else
		print_env(e->envp);
}

void			ft_env(char **av)
{
	char	**old_env;
	t_bst	*old_bin;
	t_env	*e;

	e = get_env_struct();
	old_env = e->envp;
	old_bin = e->bin_root;
	if (!*(++av))
	{
		print_env(old_env);
		return ;
	}
	do_stuff(av, e);
	ft_arrdel(&e->envp);
	ft_bstclean(&e->bin_root);
	e->envp = old_env;
	e->bin_root = old_bin;
}
