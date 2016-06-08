/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 06:13:54 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 11:00:00 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** input redirection ([n]<) handler
** usage : "cmd < file"
*/

#include "redirection.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern pid_t	g_pid;

static void		write_to_pipe(int *pipe_fd, int fd_right)
{
	int			save_fd_out;
	char		buf[BUFF_SIZE];
	ssize_t		ret;

	save_fd_out = dup(STDOUT_FILENO);
	close(pipe_fd[0]);
	while ((ret = read(fd_right, buf, BUFF_SIZE)) > 0)
		write(pipe_fd[1], buf, (size_t)ret);
	close(pipe_fd[1]);
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
	close(fd_right);
	wait(NULL);
}

static void		fork_that(char **cmd, int fd_left, int fd_right)
{
	int			pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		error(E_PIPE, NULL);
	if ((g_pid = fork()) < 0)
		error(E_FORK, NULL);
	else if (!g_pid)
		dup_exec(cmd, pipe_fd, fd_left);
	else
		write_to_pipe(pipe_fd, fd_right);
}

void			input_redirect(char **cmd)
{
	do_redirect(cmd, R_INPUT, O_RDONLY, fork_that);
}
