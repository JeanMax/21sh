/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 21:32:33 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 01:51:50 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handling forks, commands launching, and execve call
*/

#include "flex_shell.h"

extern pid_t	g_pid1;
extern pid_t	g_pid2;

static void		fork_it(char **cmd)
{
	char	**envp;
	char	*bin;
	char	*tmp;

	bin = ft_strchr(*cmd, '/') ? *cmd : get_full_bin(*cmd);
	tmp = ft_strjoin("_=", bin);
	set_env(tmp);
	ft_memdel((void *)&tmp);
	if ((g_pid2 = fork()) < 0)
		error(E_FORK, NULL);
	else if (!g_pid2)
	{
		envp = get_env_struct()->envp;
		if (bin && !access(bin, F_OK | X_OK) && execve(bin, cmd, envp))
			error(E_NOSUCHFILE, cmd[0]);
		error(E_CMDNOTFOUND, cmd[0]);
	}
	else
		wait(NULL);
}

void			launch_cmd(char **cmd)
{
	int		i;
	/* char	*tmp; */

	if (!cmd || !*cmd)
		return ;
/*
	i = -1;
	while (cmd[++i])
		if (cmd[i][0] == '$' || cmd[i][0] == '~') //?? TODO...
		{
			tmp = cmd[i];
			cmd[i] = cmd[i][0] == '~' ? \
				ft_strjoin(get_env("HOME"), cmd[i] + 1) : get_env(cmd[i] + 1);
			ft_memdel((void *)&tmp);
		}
*/
	i = 0;
	while (cmd[i])
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<')\
			|| ft_strchr(cmd[i++], '|'))
		{
			redirect(cmd, -1);
			return ;
		}
	if (!launch_builtin(cmd))
		fork_it(cmd);
}
