/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:12:49 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/09 11:15:58 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is the main...
*/

#include "line_edit.h"
#include <signal.h>

pid_t				g_pid;

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
		if (!g_pid)
			prompt();
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
		error(E_ARG, NULL);
	init();
	prompt_loop();
	ft_putendl("exit");
	return (EXIT_SUCCESS);
}
