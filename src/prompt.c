/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 17:02:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/04 18:50:52 by mcanal           ###   ########.fr       */
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

void			prompt(t_env *e)
{
	char		*user;
	char		*pwd;
	char		*home;
	int			i;

	i = 0;
	user = get_env("USER", e);
	pwd = get_env("PWD", e);
	home = get_env("HOME", e);
	i += ft_strnstr(pwd, "/private/", 9) ? 8 : 0;
	i += ft_strnstr(pwd, "/Volumes/Data/", 14) ? 13 : 0;
	if (ft_strnstr(pwd, home, ft_strlen(home)))
	{
		i += ft_strlen(home) - 1;
		pwd[ft_strlen(home) - 1] = '~';
	}
	ft_putstr_clr(user, "red");
	ft_putstr_clr("@21sh", "yellow");
	ft_putchar_clr(':', "white");
	ft_putendl_clr(pwd + i, "green");
	ft_putstr_clr("> ", "green");
	*user ? ft_memdel((void *)&user) : (void)0;
	*pwd ? ft_memdel((void *)&pwd) : (void)0;
	*home ? ft_memdel((void *)&home) : (void)0;
}

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

static void		semicolon(char *line, t_env *e)
{
	char		**sc_tab;
	char		**cmd;
	int			i;

	sc_tab = split_sc(line);
	i = 0;
	while (sc_tab[i])
	{
		if ((cmd = split_that(sc_tab[i])))
			launch_cmd(cmd, e), ft_freestab(cmd);
		i++;
	}
	ft_freestab(sc_tab);
}

void			prompt_loop(char **av, t_env *e)
{
	char		*line;
	char		**cmd;

	line = NULL;
	if (handle_pipe(&line))
	{
		if (ft_strindex(line, ';') != -1)
			semicolon(line, e);
		else if ((cmd = split_that(line)))
			launch_cmd(cmd, e), ft_freestab(cmd);
		exit(0);
	}
	prompt(e);
	while (read_stdin(&line))
	{
		ft_putendl("");
		g_pid1 = g_pid2;
		if (ft_strindex(line, ';') != -1)
				semicolon(line, e);
		else if ((cmd = split_that(line)))
			launch_cmd(cmd, e), ft_freestab(cmd);
		prompt(e);
	}
	ft_memdel((void *)&line);
	ft_exit(0, av);
}
