/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 21:32:33 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 22:36:44 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handling forks, commands launching, and execve call
*/

#include "flex_shell.h"

extern pid_t	g_pid1;
extern pid_t	g_pid2;

static void		call_execve(char **cmd, t_env *e)
{
	int			i;
	char		*join;
	char		*tmp;

	ft_freestab(e->path);
	get_path(e);
	if ((execve(cmd[0], cmd, e->env)) < 0)
	{
		(cmd[0][0] == '.' && cmd[0][1] == '/') ? error("exe", cmd[0]) : (void)0;
		i = 0;
		while ((e->path)[i])
		{
			tmp = ft_strjoin((e->path)[i++], "/");
			join = ft_strjoin(tmp, cmd[0]);
			ft_memdel((void *)&tmp);
			execve(join, cmd, e->env);
			ft_memdel((void *)&join);
		}
		error("cmd", cmd[0]);
	}
}

static void		fork_it(char **cmd, t_env *e)
{
	if ((g_pid2 = fork()) < 0)
		error("Fork", NULL);
	else if (!g_pid2)
		call_execve(cmd, e);
	else
		wait(NULL);
}

void			launch_cmd(char **cmd, t_env *e)
{
	int		i;
	char	*tmp;

	if (!cmd[0])
		return ;
	i = -1;
	while (cmd[++i])
		if (cmd[i][0] == '$' || cmd[i][0] == '~')
		{
			tmp = cmd[i];
			cmd[i] = cmd[i][0] == '~' ?\
			ft_strjoin(get_env("HOME", e), cmd[i] + 1) : get_env(cmd[i] + 1, e);
			ft_memdel((void *)&tmp);
		}
	i = 0;
	while (cmd[i])
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<')\
			|| ft_strchr(cmd[i++], '|'))
		{
			redirect(cmd, e, -1);
			return ;
		}
	is_builtin(cmd, e) ? launch_builtin(cmd, e) : fork_it(cmd, e);
}
