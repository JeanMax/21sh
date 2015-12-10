/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:48:20 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 22:30:45 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** input redirection (<) handler
** usage : "cmd < file"
*/

#include "flex_shell.h"

extern pid_t	g_pid2;

static void		fork_that(char **cmd, t_env *e, int *pipe_fd, char *all)
{
	int			save_fd0;
	int			save_fd1;

	((g_pid2 = fork()) < 0) ? error(E_FORK, NULL) : (void)0;
	if (!g_pid2)
	{
		save_fd0 = dup(0);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		launch_cmd(cmd, e), ft_freestab(cmd);
		dup2(save_fd0, 0);
		close(save_fd0);
		exit(0);
	}
	else
	{
		save_fd1 = dup(1);
		close(pipe_fd[0]);
		ft_putstr_fd(all, pipe_fd[1]);
		close(pipe_fd[1]);
		dup2(save_fd1, 1);
		close(save_fd1);
		wait(NULL);
	}
}

static void		compress_cmd(char **cmd, int i)
{
	int			j;

	j = i + 1;
	while (cmd[j] && !ft_strchr(cmd[j], '>') && !ft_strchr(cmd[j], '<')\
			&& !ft_strchr(cmd[j], '|'))
		j++;
	j = cmd[j] ? (j - i) : 0;
	i = j ? i - 1 : i;
	while (j && cmd[i++ + j])
		cmd[i] = cmd[i + j];
	while (cmd[i])
		ft_memdel((void *)&cmd[i++]);
}

void			simple_left(char **cmd, t_env *e)
{
	int			i;
	int			file_fd;
	int			pipe_fd[2];
	char		*all;

	//cmd = check_cmd(cmd); //TODO : should only accept the last input (?)
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "<"))
		i++;
	if (!cmd[i + 1])
		failn("Missing name for redirect.");
	else if (!ft_strcmp(cmd[0], "<"))
		failn("Invalid null command.");
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], "<"))
		return ;
	if ((file_fd = open(cmd[i + 1], O_RDONLY)) < 0)
	{
		error(E_OPEN | E_NOEXIT, cmd[i + 1]);
		return ;
	}
	get_all(file_fd, &all); //check return ?
	compress_cmd(cmd, i);
	close(file_fd);
	pipe(pipe_fd) < 0 ? error(E_PIPE, NULL) : (void)0;
	fork_that(cmd, e, pipe_fd, all);
	ft_memdel((void *)&all);
}
