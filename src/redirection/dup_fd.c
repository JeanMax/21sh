/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 02:05:09 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/15 20:12:54 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** will dup a fd if required, call exec_cmd recursivly, then restore fd
*/

#include "redirection.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void			dup_exec(char **cmd, int *pipe_fd, int fd_left)
{
	int			save_fd;

	save_fd = dup(fd_left);
	close(pipe_fd[fd_left == STDOUT_FILENO ? 0 : 1]);
	dup2(pipe_fd[fd_left == STDOUT_FILENO ? 1 : 0], fd_left);
	close(pipe_fd[fd_left == STDOUT_FILENO ? 1 : 0]);
	exec_cmd(cmd);
	dup2(save_fd, fd_left);
	close(save_fd);
	fd_left == STDOUT_FILENO ? (void)wait(NULL) : exit(EXIT_SUCCESS);
}

void			dup_input(char **cmd)
{
	ft_debugstr("<&", "yay");   /* debug */
	debug_arr(cmd);				/* debug */
}

void			dup_output(char **cmd)
{
	ft_debugstr(">&", "yay");   /* debug */
	debug_arr(cmd);				/* debug */
}
