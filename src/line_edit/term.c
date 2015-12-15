/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:17:50 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/15 11:49:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include <stdlib.h>
#include <unistd.h>

struct winsize	*get_term_size(void)
{
	static struct winsize	ws;

	return (&ws);
}

int				tputs_output(int i)
{
	return ((int)write(STDIN_FILENO, &i, 1));
}

int				get_cursor_col(void)
{
	char	buf[16]; //TODO: define
	char	*s;

	tputs(tgetstr("u7", NULL), 0, tputs_output);
	ft_bzero(buf, 16); //TODO: define
	s = buf;
	while (read(STDIN_FILENO, s, 1) >= 0 && *s != 'R')
		s++;
	s = buf;
	while (*s && !ft_isdigit(*s))
		s++;
//	return (ft_atoi(s)); row
	while (*s && ft_isdigit(*s))
		s++;
	while (*s && !ft_isdigit(*s))
		s++;
	return (ft_atoi(s));
}

/*
	struct termios	*get_old_term(void)
	{
	static struct termios	t;

	return (&t);
	}

	void			default_term(void)
	{
	if (!isatty(STDIN_FILENO))
	;//		error(ISATTY, NULL);

	tputs(tgetstr("ei", NULL), 0, tputs_output);
	if (tcsetattr(STDIN_FILENO, 0, get_old_term()))
	;//error(SETATTR, NULL);
	}

	void			raw_term(void)
	{
	char					term_buf[2048]; //TODO: any define?
	struct termios			term;

	if (!isatty(STDIN_FILENO))
	;//		error(ISATTY, NULL);
	if (tcgetattr(STDIN_FILENO, &term))
	;//error(GETATTR, NULL);

	term.c_lflag &= (unsigned int)~(ICANON);
	term.c_lflag &= (unsigned int)~(ECHO);
	term.c_cc[VTIME] = 0;
	term.c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term))
	;//error(SETATTR, NULL);
	if (tgetent(term_buf, getenv("TERM")) == ERR)
	;//error(TERM, NULL);
	tputs(tgetstr("im", NULL), 0, tputs_output);
	}
*/
void			switch_term(void)
{
	char					term_buf[2048];
	struct termios			term;
	static struct termios	*old_term = NULL;

	if (tcgetattr(STDIN_FILENO, &term))
		error(E_GETATTR, NULL);
	if (!old_term && (old_term = (struct termios *)malloc(sizeof(term))))
		ft_memcpy(old_term, &term, sizeof(struct termios));
	else
	{
		tputs(tgetstr("ei", NULL), 0, tputs_output);
		if (tcsetattr(STDIN_FILENO, 0, old_term))
			error(E_SETATTR, NULL);
		old_term ? ft_memdel((void *)&old_term) : (void)0;
		return ;
	}
	term.c_lflag &= (unsigned int)~(ICANON);
	term.c_lflag &= (unsigned int)~(ECHO);
	term.c_cc[VTIME] = 0;
	term.c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term))
		error(E_SETATTR, NULL);
	if (tgetent(term_buf, getenv("TERM")) == ERR)
		error(E_TERM, NULL); //TODO: exec none interactive mod?
	tputs(tgetstr("im", NULL), 0, tputs_output);
}
