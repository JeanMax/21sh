/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:58:39 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/15 11:06:30 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include <unistd.h>

/*
 //debug
#include <stdio.h>
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

//start with null pointer bro!
t_bool			read_notty_brute(char **line)
{
	ft_memdel((void *)line);
	if (get_next_line(STDIN_FILENO, line) != 1)
		return (FALSE);
	return (*line ? TRUE : FALSE);
}

t_bool			read_notty(char **line)
{
	char		*swap;
	t_cursor	*c;

	c = get_cursor();
	if (get_next_line(STDIN_FILENO, line) != 1)
		return (FALSE);
	if ((swap = *line))
		while (*swap)
			ft_laddlast(&c->first_l, ft_lnew((void *)swap++, 1));
	ft_memdel((void *)line);
	*line = to_string();
	ft_lclean(&c->first_l);
	return (*line ? TRUE : FALSE);
}

//start with null pointer bro!
t_bool			read_tty_brute(char **line)
{
	t_cursor	*c;
	char		buf[KEY_BUF_SIZE + 1];
	char		*swap;

	switch_term();
	c = get_cursor();
	c->current_l = NULL;
	c->prompt_len = (size_t)get_cursor_col() - 1;

	if (!(*line = read_loop(buf, KEEP_READING)))
		ft_lclean(&c->first_l);
	swap = *line;
	while (*swap && c->first_l)
	{
		*(swap++) = *(char *)(c->first_l->content);
		c->first_l = c->first_l->next;
	}
	*swap = 0;
	c->first_l = NULL;

	switch_term();
	return (*line ? TRUE : FALSE);
}

//start with null pointer bro!
t_bool			read_tty(char **line)
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
