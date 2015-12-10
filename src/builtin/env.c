/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 07:42:03 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/27 21:55:45 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** env builtin
*/

#include "flex_shell.h"

static char		**check_cmd(char **av)
{
	int	i;

	i = 1;
	if (av[1])
		while (av[i])
		{
			if (ft_strindex(av[i], '=') != -1 || !ft_strcmp(av[i], "-i"))
				i++;
			else
				break ;
		}
	if (av[i])
		return (av += i);
	else
		return (NULL);
}

static void		list_env(char *s, t_env *e)
{
	if (e->first_l)
		ft_ladd(&(e->first_l), ft_lnew((void *)s, ft_strlen(s)));
	else
		e->first_l = ft_lnew((void *)s, ft_strlen(s));
}

static void		edit_env(char **av, char **ae, t_env *e)
{
	int		i;
	int		j;
	int		count;
	char	*env_var;

	i = 0;
	if (av[1] && !ft_strcmp("-i", av[1]) && ae)
		while (ae[i])
			ae[i++] = NULL;
	i = 0;
	while (av[i])
	{
		if ((count = ft_strindex(av[i], '=') != -1))
		{
			env_var = ft_strsub(av[i], 0, (size_t)count);
			j = 0;
			while (ae[j] && ft_strncmp(ae[j], env_var, ft_strlen(env_var)))
				j++;
			!ae[j] ? list_env(av[i], e) : (void)0;
			ae[j] = ae[j] ? ft_strdup(av[i]) : ae[j];
			ft_memdel((void *)&env_var);
		}
		i++;
	}
}

void			ft_env(char **av, t_env *e)
{
	int		i;
	char	**cmd;
	char	**new_ae;
	t_lst	*tmp;

	i = 0;
	e->first_l = NULL;
	cmd = check_cmd(av);
	new_ae = ft_cpystab(e->env, NULL);
	edit_env(av, new_ae, e);
	if (!cmd && new_ae)
		while (new_ae[i])
			ft_putendl(new_ae[i++]);
	tmp = e->first_l;
	while (tmp && !cmd)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
	av = e->env;
	e->env = new_ae;
	cmd ? launch_cmd(&cmd[0], e) : (void)0;
	e->env = av;
	new_ae ? ft_freestab(new_ae) : (void)0;
	e->first_l ? ft_lclean(&(e->first_l)) : (void)0;
}
