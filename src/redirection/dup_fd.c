/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 02:05:09 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 15:13:37 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** will dup a fd if required, call exec_cmd recursivly, then restore fd
** [n]<&word  /  [n]>&word
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
	/* debug_arr(cmd);				/\* debug *\/ */
	/* ft_debugnbr("pid", g_pid);	/\* debug *\/ */
	/* ft_debugnbr("fd", fd_left);	/\* debug *\/ */
	fd_left == STDOUT_FILENO ? (void)wait(NULL) : exit(EXIT_SUCCESS);
}

static void		just_dup_it(char **cmd, int default_left_fd)
{
	char	**swap;
	int		fd_left;
	int		fd_right;
	int		fd_save;

	fd_left = -1;
	fd_right = -1;
	swap = cmd;
	while (*swap && !is_redirection(*swap))
		swap++;
	if (*swap)
	{
		if ((fd_left = get_fd(*swap)) == -1)
			fd_left = default_left_fd;
		ft_arrdelone(cmd, *swap);
		fd_right = get_fd(*swap);
		if (fd_right == -1 && !ft_strcmp(*swap, "-") && fd_left != -1)
			fd_right = -42;
		ft_arrdelone(cmd, *swap);
	}
	if (fd_left == -1 || fd_right == -1 || fd_left == fd_right)
	{
		failn("21sh: Invalid file descriptor.");
		ft_arrdel(&cmd);
		return ;
	}
	fd_save = dup(fd_left);
	fd_right == -42 ? close(fd_left) : dup2(fd_right, fd_left);
	exec_cmd(cmd);
	dup2(fd_save, fd_left);
	close(fd_save);
	ft_arrdel(&cmd);
}

void			dup_input(char **cmd)
{
	just_dup_it(ft_arrdup(cmd), STDIN_FILENO);
}

void			dup_output(char **cmd)
{
	just_dup_it(ft_arrdup(cmd), STDOUT_FILENO);
}
