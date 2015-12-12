/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:58:39 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 00:28:06 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flex_shell.h"
#include <stdio.h>

/*
 //debug
static void	debug_list(t_lst *link)
{
	if (!link)
	{
		write(1, "|\n", 2);
		return ;
	}
	write(1, "|", 1);
	write(1, link->content, 1);
	debug_list(link->next);
}


static enum e_status debug_buf(char *buf)
{
	printf("\\x%lx\\x%lx\\x%lx\\x%lx\\x%lx\\x%lx\n",		 \
		   (unsigned long)buf[0], (unsigned long)buf[1],	 \
		   (unsigned long)buf[2], (unsigned long)buf[3],		\
		   (unsigned long)buf[4], (unsigned long)buf[5]);
	fflush(stdout);
	return (KEEP_TRYING);
}
*/

 //debug

static void		*get_f_array(void)
{
	static enum e_status	(*f[])(char *) = //static?
		{
			/* debug_buf,			/\* debug *\/ */
			clear_term,
			del,
			backspace,
			copy,
			cut_forward,
			cut_backward,
			paste,
			move_left,
			move_right,
			move_up,
			move_down,
			move_begin,
			move_end,
			move_next_word,
			move_prev_word,
			set_history,
			get_history,
			insert, //need to be last...
			NULL
		};
	return ((void *)f);
}
enum e_status	do_stuff_with_key(char *buf)
{
	enum e_status	status;
	enum e_status	(**f)(char *);

	status = KEEP_TRYING;
	f = get_f_array();
	while (*f && status == KEEP_TRYING)
		status = (*(f++))(buf);
	return (status);

}

static char		*read_loop(char *buf, enum e_status status)
{
	ft_bzero(buf, KEY_BUF_SIZE + 1);

	if (status == CMD_DONE)
		return (to_string());
	if (status == STOP_READING || (read(STDIN_FILENO, buf, KEY_BUF_SIZE)) < 0)
		return (NULL);

	return (read_loop(buf, do_stuff_with_key(buf)));
}

t_bool			handle_pipe(char **line)
{
	char		buf;
	t_cursor	*c;

	switch_term();
	c = get_cursor();
	tputs(tgetstr("u7", NULL), 0, tputs_output);
	while (read(STDIN_FILENO, &buf, 1) > 0)
	{
		ft_laddlast(&c->first_l, ft_lnew((void *)&buf, 1));
		if (c->first_l && c->first_l->next 
			&& *(char *)c->first_l->content == '\033'
			&& *(char *)c->first_l->next->content == '[')
		{
			ft_lclean(&c->first_l);
			c->first_l = NULL;
			while (read(STDIN_FILENO, &buf, 1) > 0 && buf != 'R')
				;
			switch_term();
			return (FALSE);
		}
	}
	*line = to_string();
	ft_lclean(&c->first_l);
	switch_term();
	return (TRUE);
}

//start with null pointer bro!
t_bool			read_stdin(char **line)
{
	t_cursor	*c;
	char		buf[KEY_BUF_SIZE + 1];

	switch_term();
	c = get_cursor();
	c->current_l = NULL;
	c->prompt_len = (size_t)get_cursor_col() - 1;

	if (!(*line = read_loop(buf, KEEP_READING)))
		ft_lclean(&c->first_l);
	c->first_l = NULL;

	switch_term();
	return (*line ? TRUE : FALSE);
}
