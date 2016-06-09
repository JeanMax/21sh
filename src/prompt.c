/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 17:02:18 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/09 12:00:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handle prompt loop
** print a pretty prompt
** split line in a tab (space and tab as separators, handle; " and ')
*/

#include "line_edit.h"
#include <stdlib.h>
#include <unistd.h>

extern pid_t	g_pid;

void			prompt(void)
{
	char		*env1;
	char		*env2;

	env1 = get_env("USER");
	ft_putstr_clr(env1 ? env1 + 5 : "marvin", "red");
	ft_putstr_clr("@21sh", "yellow");
	ft_putchar_clr(':', "white");
	if (!(env1 = get_env("PWD")))
		ft_putendl_clr("TheVoid", "green");
	else if (!(env2 = get_env("HOME")))
		ft_putendl_clr(env1 + 4, "green");
	else if (ft_strstr(env1 + 4, env2 + 5))
	{
		ft_putchar_clr('~', "green");
		ft_putendl_clr(env1 + 4 + ft_strlen(env2 + 5), "green");
	}
	else
		ft_putendl_clr(env1 + 4, "green");
	ft_putstr_clr("> ", "green");
}

static void		do_something_with_line(char *line)
{
	char		**swap;
	char		**cmd_arr;
	char		**cmd;

	if (!line || ft_strlen(line) > LINE_SIZE \
			|| !(cmd_arr = ft_strsplit(line, S_LINE)))
		return ;
	swap = cmd_arr;
	while (*swap)
		if ((cmd = ft_strsplit(*(swap++), S_WORD)))
		{
			exec_cmd(cmd);
			ft_arrdel(&cmd);
		}
	ft_arrdel(&cmd_arr);
}

void			prompt_loop(void)
{
	t_bool		(*read_it)(char **);
	char		*line;

	line = NULL;
	read_it = (!isatty(STDIN_FILENO) || !get_env("TERM") || \
	ft_strcmp("xterm-256color", get_env("TERM") + 5)) ? read_notty : read_tty;
	if (!isatty(STDIN_FILENO))
	{
		while (read_it(&line))
			do_something_with_line(line);
		exit(EXIT_SUCCESS);
	}
	prompt();
	while (read_it(&line))
	{
		ft_putendl("");
		do_something_with_line(line);
		prompt();
	}
}
