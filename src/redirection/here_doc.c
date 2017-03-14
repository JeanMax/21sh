/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 22:48:29 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/22 23:12:41 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** here document (<<) handler
*/

#include "redirection.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern pid_t	g_pid;

static void		get_text(char **text, char *here, t_bool (*read_it)(char **))
{
	char			*buf;
	char			*tmp;
	size_t			len;

	*text = ft_strnew(1);
	if (isatty(STDIN_FILENO))
		ft_putstr("? ");
	buf = NULL;
	while (read_it(&buf) && ft_strcmp(buf, here))
	{
		tmp = ft_strjoin(buf, "\n");
		if (isatty(STDIN_FILENO))
			ft_putstr("\n? ");
		len = ft_strlen(*text);
		*text = (char *)ft_realloc((void *)*text, len, len + ft_strlen(tmp));
		ft_strcat(*text, tmp);
		ft_memdel((void *)&tmp);
	}
	/* ft_memdel((void *)&buf); */
	if (isatty(STDIN_FILENO))
		ft_putchar('\n');
}

static void		write_to_pipe(char *here, int *pipe_fd)
{
	int			save_fd_out;
	char		*text;

	get_text(&text, here, \
				isatty(STDIN_FILENO) ? read_tty_brute : read_notty_brute);
	save_fd_out = dup(STDOUT_FILENO);
	close(pipe_fd[0]);
	ft_putstr_fd(text, pipe_fd[1]);
	ft_memdel((void *)&text);
	close(pipe_fd[1]);
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
	wait(NULL);
}

static void		fork_that(char **cmd, char *here)
{
	int			pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		error(E_PIPE, NULL);
	if ((g_pid = fork()) < 0)
		error(E_FORK, NULL);
	else if (!g_pid)
		dup_exec(cmd, pipe_fd, STDIN_FILENO);
	else
		write_to_pipe(here, pipe_fd);
}

void			here_doc(char **cmd)
{
	char	**swap;
	char	**new_cmd;

	swap = cmd;
	while (*(++swap) && !ft_strchr(*swap, R_HERE_DOC))
		;
	new_cmd = (char **)malloc(sizeof(char *) * (size_t)(swap - cmd + 1));
	swap = new_cmd;
	while (!ft_strchr(*cmd, R_HERE_DOC) && (*(swap++) = *(cmd++)))
		;
	*swap = NULL;
	fork_that(new_cmd, *(++cmd));
	ft_memdel((void *)&new_cmd);
	exec_cmd(++cmd);
}
