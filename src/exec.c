/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 21:32:33 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 14:13:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handling forks, commands execing, and execve call
*/

#include "flex_shell.h"
#include <sys/wait.h>
#include <unistd.h>

extern pid_t	g_pid;

static void		fork_it(char **cmd)
{
	char	**envp;
	char	*bin;
	char	*tmp;

	bin = ft_strchr(*cmd, '/') ? *cmd : get_full_bin(*cmd);
	tmp = ft_strjoin("_=", bin);
	set_env(tmp);
	ft_memdel((void *)&tmp);
	if ((g_pid = fork()) < 0)
		error(E_FORK, NULL);
	else if (!g_pid)
	{
		envp = get_env_struct()->envp;
		if (bin && !access(bin, X_OK) && execve(bin, cmd, envp))
			error(E_NOSUCHFILE, cmd[0]);
		error(E_CMDNOTFOUND, cmd[0]);
	}
	else
		wait(NULL);
	g_pid = 0;
}

void			exec_cmd(char **cmd)
{
	if (cmd && *cmd && !exec_redirection(cmd) && !exec_builtin(cmd))
		fork_it(cmd);
}
