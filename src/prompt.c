/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 17:02:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 03:13:21 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handle prompt loop
** print a pretty prompt
** split line in a tab (space and tab as separators, handle ; " and ')
*/

#include "flex_shell.h"

extern pid_t	g_pid1; //TODO: clean these
extern pid_t	g_pid2; //TODO: clean these

void			prompt(void)
{
	char		*env1;
	char		*env2;


	env1 = get_env("USER");
	ft_putstr_clr(env1 ? env1 + 5 : "marvin", "red");
	ft_putstr_clr("@21sh", "yellow");
	ft_putchar_clr(':', "white");

	if (!(env1 = get_env("PWD"))) //berk
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

	/* i += ft_strnstr(pwd, "/private/", 9) ? 8 : 0; */
	/* i += ft_strnstr(pwd, "/Volumes/Data/", 14) ? 13 : 0; */
}

/*
static char		**split_that(char *s)
{
	int			i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
		{
			s[i] = -42;
			while (s[++i] != '\'')
				if (!s[i])
					return (failn("Unmatched \'."));
			s[i] = -42;
		}
		else if (s[i] == '\"')
		{
			s[i] = -42;
			while (s[++i] != '\"')
				if (!s[i])
					return (failn("Unmatched \"."));
			s[i] = -42;
		}
		else if (s[i] == ' ' || s[i] == '\t')
			s[i] = -42;
	}
	return (ft_strsplit(s, -42));
}
*/
/*
static char		**split_sc(char *s)
{
	int			i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
		{
			while (s[++i] != '\'')
				if (!s[i])
					return (NULL);
		}
		else if (s[i] == '\"')
		{
			while (s[++i] != '\"')
				if (!s[i])
					return (NULL);
		}
		else if (s[i] == ';')
			s[i] = -42;
	}
	return (ft_strsplit(s, -42));
}
*/
static void		multi_lines(char *line)
{
	char		**sc_tab;
	char		**cmd;
	int			i;

	sc_tab = ft_strsplit(line, S_LINE);
	i = 0;
	while (sc_tab[i])
	{
		if ((cmd = ft_strsplit(sc_tab[i], S_WORD)))
		{
			launch_cmd(cmd);
			ft_arrdel(&cmd);
		}
		i++;
	}
	ft_arrdel(&sc_tab);
}

void			prompt_loop(void)
{
	char		*line;
	char		**cmd;

	line = NULL;
	if (handle_pipe(&line))
	{
		if (ft_strchr(line, S_LINE))
			multi_lines(line);
		else if ((cmd = ft_strsplit(line, S_WORD)))
			launch_cmd(cmd), ft_arrdel(&cmd);
		exit(0);
	}
	prompt();
	while (read_stdin(&line))
	{
		ft_putendl("");
		g_pid1 = g_pid2;
		if (ft_strchr(line, S_LINE))
			multi_lines(line);
		else if ((cmd = ft_strsplit(line, S_WORD)))
			launch_cmd(cmd), ft_arrdel(&cmd);
		prompt();
	}
	ft_memdel((void *)&line);
}
