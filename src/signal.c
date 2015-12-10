/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 20:13:58 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 04:24:50 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** signal handling and init function (get env and builtin foncions list)
*/

#include "flex_shell.h"

pid_t				g_pid1;
pid_t				g_pid2;
t_env				*g_env;

static void			sig_handl(int sig)
{
	if (sig == SIGBUS)
		error("bus", NULL);
	else if (sig == SIGSEGV)
		error("seg", NULL);
	else if (sig == SIGFPE)
		error ("fpe", NULL);
	else if (sig == SIGINT)
	{
		move_end(NULL);
		clean_cursor();
		ft_putendl("");
//		ft_putstr("\b \b\b \b\n");
		if (g_pid1 == g_pid2 || (!g_pid1 && !g_pid2))
			prompt(g_env);
		g_pid1 = g_pid2;
	}
	else if (sig == SIGWINCH)
		ioctl(0, TIOCGWINSZ, get_term_size());
	else if (sig == 29)
		prompt(g_env);
}

void				init(int ac, char **ae, t_env *e)
{
	ac > 1 ? error("arg", NULL) : (void)0;
	signal(SIGWINCH, sig_handl);
	signal(SIGINT, sig_handl);
	ioctl(0, TIOCGWINSZ, get_term_size());
	signal(SIGINT, sig_handl);
	signal(SIGFPE, sig_handl);
	signal(29, sig_handl);
	signal(SIGSEGV, sig_handl);
	signal(SIGBUS, sig_handl);
	signal(SIGTSTP, SIG_IGN); //TODO
	signal(SIGQUIT, SIG_IGN); //TODO
	e->env = ft_cpystab(ae, NULL);
	get_path(e);
	e->builtin = malloc(6 * sizeof(char *));
	(e->builtin)[0] = ft_strdup("cd");
	(e->builtin)[1] = ft_strdup("setenv");
	(e->builtin)[2] = ft_strdup("unsetenv");
	(e->builtin)[3] = ft_strdup("env");
	(e->builtin)[4] = ft_strdup("exit");
	(e->builtin)[5] = ft_strnew(1);
	g_env = e;
//	ft_putstr("\033[2J\033[1;1H");
}
