/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:46:30 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/15 01:16:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** get $PATH from env (**ae);
** set an entry of env var
** get the appropriate env entry
*/

#include "flex_shell.h"

char	**set_av(char *s1, char *s2, t_env *e, int go)
{
	char		**av;
	char		tmp;
	struct stat	s;

	av = malloc(sizeof(char *) * 4);
	av[0] = ft_strdup("setenv");
	av[1] = ft_strdup(s1);
	av[2] = (!ft_strcmp(s2, "PWD") || !ft_strcmp(s2, "OLDPWD") ||\
		!ft_strcmp(s2, "HOME")) ? get_env(s2, e) : ft_strdup(s2);
	av[3] = NULL;
	tmp = go ? (char)chdir(av[2]) : '\0';
	if (tmp && go)
		ft_putstr(stat(s2, &s) ?\
			"cd: no such file or directory: " : "cd: not a directory: ");
	if (tmp && go)
		ft_putendl(ft_strrindex(s2, '/') != (int)ft_strlen(s2) - 1 ?\
					s2 + ft_strrindex(s2, '/') + 1 : s2);
	return (av);
}

char	*get_env(char *var, t_env *e)
{
	char	**ae;
	int		i;
	size_t	len;

	ae = e->env;
	i = 0;
	len = ft_strlen(var);
	while (ae[i] && ft_strncmp(ae[i], var, (int)len > ft_strindex(ae[i], '=') \
							   ? len : (size_t)ft_strindex(ae[i], '=')))
		i++;
	return (ae[i] ? ft_strdup(ae[i] + len + 1) : ft_strnew(1));
}

void	get_path(t_env *e)
{
	char	*tmp;
	int		i;
	char	**av;

	i = -1;
	while ((e->env)[++i])
		if ((e->env)[i][0] == 'P' && (e->env)[i][1] == 'A' && (e->env)[i][2] ==\
			'T' && (e->env)[i][3] == 'H' && (e->env)[i][4] == '=')
			break ;
	if (!(e->env)[i])
	{
		av = set_av("PATH", "/bin", e, 0);
		launch_builtin(av, e);
		ft_freestab(av);
		av = set_av("USER", "marvin", e, 0);
		launch_builtin(av, e);
		ft_freestab(av);
	}
	tmp = ft_strdup((e->env)[i]);
	e->path = ft_strsplit(tmp + 5, ':');
	ft_memdel((void *)&tmp);
}
