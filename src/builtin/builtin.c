/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 08:00:25 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 01:07:48 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** launch the appropriatte builtin function
*/

#include "flex_shell.h"

//return 0 if it's not, otherwise return the index + 1
static int		is_builtin(char *cmd)
{
	int			i;
	const char	*built_name[] = \
		{ "exit", "env", "setenv", "unsetenv", "cd", NULL };

	i = 0;
	while (built_name[i] && cmd && ft_strcmp(built_name[i], cmd))
		i++;
	return (built_name[i] && cmd ? i + 1 : FALSE);
}

//return true and launch builtin if it was a builtin, otherwise return false
t_bool			launch_builtin(char **av)
{
	int			built_index;
	char		*tmp;
	void		(*builtin[])(char **) = \
		{ ft_exit, ft_env, ft_setenv, ft_unsetenv, ft_cd };

	if (!(built_index = is_builtin(*av)))
		return (FALSE);

	tmp = ft_strjoin("_=builtin/", *av);
	set_env(tmp);
	ft_memdel((void *)&tmp);
	builtin[built_index - 1](av);
	return (TRUE);
}
