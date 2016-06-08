/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 00:51:45 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/07 11:42:12 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** output redirection (>) handler
** usage : "cmd [n]> file"
**
** output append redirection (>>) handler
** usage : "cmd [n]>> file"
*/

#include "redirection.h"
#include <unistd.h>

static void		dup_fd(char **cmd, int fd_left, int fd_right)
{
	int	fd_save;

	fd_save = dup(fd_left);
	dup2(fd_right, fd_left);
	exec_cmd(cmd);
	dup2(fd_save, fd_left);
	close(fd_right);
	close(fd_save);
}

void			output_append_redirect(char **cmd)
{
	do_redirect(cmd, R_OUTPUT_APPEND, O_WRONLY | O_CREAT | O_APPEND, dup_fd);
}

void			output_redirect(char **cmd)
{
	do_redirect(cmd, R_OUTPUT, O_WRONLY | O_CREAT | O_TRUNC, dup_fd);
}
