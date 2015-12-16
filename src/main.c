/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:12:49 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/15 12:14:47 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is the main...
*/

/* #include "flex_shell.h" */
#include "line_edit.h"
#include <signal.h> //works without...

pid_t				g_pid1; //TODO: move to header / delete
pid_t				g_pid2;

static void		inc_shlvl(void)
{
	char		*shlvl1;
	char		*shlvl2;

	if (!(shlvl1 = get_env("SHLVL")))
	{
		set_env("SHLVL=1");
		return ;
	}
	shlvl1 = ft_itoa(ft_atoi(shlvl1 + 6) + 1);
	shlvl2 = ft_strjoin("SHLVL=", shlvl1);
	set_env(shlvl2);
	ft_memdel((void *)&shlvl1);
	ft_memdel((void *)&shlvl2);
}

static void		sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		move_end(NULL);
		clean_cursor();
		ft_putendl("");
//		ft_putstr("\b \b\b \b\n");
		if (g_pid1 == g_pid2 || (!g_pid1 && !g_pid2)) //TODO...
			prompt();
		g_pid1 = g_pid2; //TODO...
	}
	else if (sig == SIGWINCH)
	{
		ioctl(0, TIOCGWINSZ, get_term_size());
		clear_term(NULL);
	}
	else if (sig == SIGINFO)
		prompt();
}

static void		init(void)
{
	extern char	**environ;

	get_env_struct()->envp = ft_arrdup(environ);
	inc_shlvl();
	update_bin(TRUE);
	ioctl(0, TIOCGWINSZ, get_term_size());
	signal(SIGINT, sig_handl);
	signal(SIGWINCH, sig_handl);
	signal(SIGINFO, sig_handl);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int				main(int ac, char **av)
{
	(void)av;
	if (ac > 1)
		error(E_ARG | E_NOEXIT, NULL); /* debug */
	init();
	prompt_loop();
	ft_putendl("exit");
	return (EXIT_SUCCESS);
}
