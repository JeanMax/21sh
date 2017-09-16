/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 17:02:18 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/16 23:27:25 by mc               ###   ########.fr       */
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
	ft_putstr_clr(env1 ? env1 + 5 : "marvin", CLR_RED);
	ft_putstr_clr("@21sh", CLR_YELLOW);
	ft_putchar_clr(':', CLR_WHITE);
	if (!(env1 = get_env("PWD")))
		ft_putendl_clr("TheVoid", CLR_GREEN);
	else if (!(env2 = get_env("HOME")))
		ft_putendl_clr(env1 + 4, CLR_GREEN);
	else if (ft_strstr(env1 + 4, env2 + 5))
	{
		ft_putchar_clr('~', CLR_GREEN);
		ft_putendl_clr(env1 + 4 + ft_strlen(env2 + 5), CLR_GREEN);
	}
	else
		ft_putendl_clr(env1 + 4, CLR_GREEN);
	ft_putstr_clr("> ", CLR_GREEN);
}

static void		do_something_with_line(char *line)
{
	char		**swap;
	char		**cmd_arr;
	char		**cmd;

	if (!line)
		return ;
	if (ft_strlen(line) > LINE_SIZE * 10)
		failn("21sh: expression over 9000!");
	if (!(cmd_arr = ft_strsplit(line, S_LINE)))
		return ;
	swap = cmd_arr;
	while (*swap)
		if ((cmd = ft_strsplit(*(swap++), S_WORD)))
		{
			exec_cmd(cmd);
			ft_arr_del(&cmd);
		}
	ft_arr_del(&cmd_arr);
}

/*
** read_it actually returns a t_bool, but norme blabla fuck it blabla
*/

void			prompt_loop(void)
{
	char		*line;
	int			(*read_it)(char **);

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
