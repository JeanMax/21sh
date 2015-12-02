/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:40:39 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/15 01:19:04 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** setenv builtin
*/

#include "header.h"

static void		var_exist(t_env *e, char *var, char *val)
{
	int		j;
	char	**tmp;

	j = 0;
	while ((e->env)[j] && ft_strncmp((e->env)[j], var,
						(int)ft_strlen(var) > ft_strindex((e->env)[j], '=') ?
						ft_strlen(var) : (size_t)ft_strindex((e->env)[j], '=')))
		j++;
	if ((e->env)[j])
	{
		ft_memdel((void *)&(e->env)[j]);
		(e->env)[j] = ft_strdup(val);
	}
	else
	{
		tmp = e->env;
		e->env = ft_cpystab(e->env, val);
		ft_freestab(tmp);
	}
}

void			ft_setenv(char **av, t_env *e)
{
	char	*to_add;
	char	*tmp;
	int		ac;

	ac = 0;
	while (av[ac])
		ac++;
	ac == 1 ? ft_strcpy(av[0], "env") : NULL;
	ac == 1 ? launch_builtin(av, e) : (void)0;
	ac > 3 ? ft_putendl("setenv: Too many arguments.") : (void)0;
	if (ac == 1 || ac > 3)
		return ;
	if (ft_strindex(av[1], '=') != -1)
	{
		ft_putendl("setenv: Syntax Error.");
		return ;
	}
	tmp = ft_strjoin(av[1], "=");
	to_add = ft_strjoin(tmp, av[2]);
	var_exist(e, av[1], to_add);
	ft_memdel((void *)&tmp);
	ft_memdel((void *)&to_add);
}
