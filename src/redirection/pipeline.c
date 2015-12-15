/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 05:38:56 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/15 08:36:25 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pipe (|) handler
** usage "cmd | cmd"
*/

#include "redirection.h"
#include <unistd.h>

extern pid_t	g_pid2;

static void		fork_that(char **cmd1, char **cmd2)
{
	int			pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		error(E_PIPE, NULL);
	if ((g_pid2 = fork()) < 0)
		error(E_FORK, NULL);
	else if (!g_pid2)
		dup_exec(cmd2, pipe_fd, STDIN_FILENO);
	else
		dup_exec(cmd1, pipe_fd, STDOUT_FILENO);
}

void			pipeline(char **cmd)
{
	char	**swap;
	char	**new_cmd;

	swap = cmd;
	while (*(++swap) && !ft_strchr(*swap, R_PIPELINE))
		;
	new_cmd = (char **)malloc(sizeof(char *) * (size_t)(swap - cmd + 1));
	swap = new_cmd;
	while (!ft_strchr(*cmd, R_PIPELINE) && (*(swap++) = *(cmd++)))
		;
	*swap = NULL;
	fork_that(new_cmd, ++cmd);
	ft_memdel((void *)&new_cmd);
}
