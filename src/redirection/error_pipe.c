/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 23:21:24 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 22:28:55 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stderr pipe handler (|&)
** this is also redirecting stdout
*/

#include "flex_shell.h"

extern pid_t	g_pid2;

static void		child(int *pipe_fd, char **cmd2)
{
	int			save_fd0;

	save_fd0 = dup(0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	launch_cmd(cmd2);
	dup2(save_fd0, 0);
	close(save_fd0);
	exit(0);
}

static void		father(int *pipe_fd, char **cmd1)
{
	int			save_fd1;
	int			save_fd2;

	save_fd1 = dup(1);
	save_fd2 = dup(2);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	dup2(pipe_fd[1], 2);
	close(pipe_fd[1]);
	launch_cmd(cmd1);
	dup2(save_fd1, 1);
	dup2(save_fd2, 2);
	close(save_fd1);
	close(save_fd2);
	wait(NULL);
}

static void		fork_that(char **cmd1, char **cmd2)
{
	int			pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		error(E_PIPE, NULL);
	if ((g_pid2 = fork()) < 0)
		error(E_FORK, NULL);
	else if (!g_pid2)
		child(pipe_fd, cmd2);
	else
		father(pipe_fd, cmd1);
}

void			error_pipe(char **cmd)
{
	int			i;
	char		**new_cmd;

	//cmd = check_cmd(cmd); //TODO
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "|&"))
		i++;
	if (!ft_strcmp(cmd[0], "|&") || !cmd[i + 1])
		failn("Invalid null command.");
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], "|&"))
		return ;
	new_cmd = ft_arrdup(&cmd[i + 1]);
	while (cmd[i])
		ft_memdel((void *)&cmd[i++]);
	fork_that(cmd, new_cmd);
	ft_arrdel(&new_cmd);
}
