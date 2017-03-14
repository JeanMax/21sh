/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 08:00:25 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/22 22:36:13 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exec the appropriatte builtin function
*/

#include "builtin.h"

/*
** return 0 if it's not, otherwise return the index + 1
*/

static int		is_builtin(char *cmd)
{
	int				i;
	const char		*built_name[] = {
		"exit",
		"env",
		"setenv",
		"unsetenv",
		"cd",
		"echo",
		NULL
	};

	i = 0;
	while (built_name[i] && cmd && ft_strcmp(built_name[i], cmd))
		i++;
	return (built_name[i] && cmd ? i + 1 : FALSE);
}

/*
** return true and exec builtin if it was a builtin, otherwise return false
*/

t_bool			exec_builtin(char **cmd)
{
	int			built_index;
	char		*tmp;
	void		(*const builtin[])(char **) = {
		ft_exit,
		ft_env,
		ft_setenv,
		ft_unsetenv,
		ft_cd,
		ft_echo
	};

	if (!(built_index = is_builtin(*cmd)))
		return (FALSE);
	tmp = ft_strjoin("_=builtin/", *cmd);
	set_env(tmp);
	ft_memdel((void *)&tmp);
	builtin[built_index - 1](cmd);
	return (TRUE);
}
