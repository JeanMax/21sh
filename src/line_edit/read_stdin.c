/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:58:39 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 21:42:31 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
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
*/

static void debug_buf(char *buf)
{
	printf("\\x%lx\\x%lx\\x%lx\\x%lx\\x%lx\\x%lx\n",		 \
		   (unsigned long)buf[0], (unsigned long)buf[1],	 \
		   (unsigned long)buf[2], (unsigned long)buf[3],		\
		   (unsigned long)buf[4], (unsigned long)buf[5]);
	fflush(stdout);
}
 //debug
 
static t_bool	read_loop(char *buf)
{
	ft_bzero(buf, KEY_BUF_SIZE + 1);
    if ((read(STDIN_FILENO, buf, KEY_BUF_SIZE)) < 0)
		return (FALSE);

	if (!memcmp(buf, K_RETURN, KEY_BUF_SIZE))
		return (TRUE);
	if (!memcmp(buf, K_CTRL_D, KEY_BUF_SIZE))
	{
		if (!get_cursor()->first_l)
			return (FALSE);
		else
			del();
	} 
	else if (!memcmp(buf, K_CTRL_L, KEY_BUF_SIZE))
		clear_term();
	else if (!memcmp(buf, K_DEL, KEY_BUF_SIZE))
		del();
	else if (!memcmp(buf, K_BACKSPACE, KEY_BUF_SIZE))
		backspace();
	else if (!memcmp(buf, K_F3, KEY_BUF_SIZE))
		copy();
	else if (!memcmp(buf, K_F5, KEY_BUF_SIZE))
		cut_forward();
	else if (!memcmp(buf, K_F6, KEY_BUF_SIZE))
		cut_backward();
	else if (!memcmp(buf, K_F4, KEY_BUF_SIZE))
		paste();
	else if (!memcmp(buf, K_LEFT, KEY_BUF_SIZE))
		move_left();
	else if (!memcmp(buf, K_RIGHT, KEY_BUF_SIZE))
		move_right();
	else if (!memcmp(buf, K_CTRL_DOWN, KEY_BUF_SIZE))
		move_down();
	else if (!memcmp(buf, K_CTRL_UP, KEY_BUF_SIZE))
		move_up();
	else if (!memcmp(buf, K_CTRL_RIGHT, KEY_BUF_SIZE) \
			 || !memcmp(buf, K_ALT_F, KEY_BUF_SIZE))
		move_next_word();
	else if (!memcmp(buf, K_CTRL_LEFT, KEY_BUF_SIZE) \
			 || !memcmp(buf, K_ALT_B, KEY_BUF_SIZE))
		move_prev_word();
	else if (!memcmp(buf, K_START, KEY_BUF_SIZE) \
			 || !memcmp(buf, K_CTRL_A, KEY_BUF_SIZE))
		move_begin();
	else if (!memcmp(buf, K_END, KEY_BUF_SIZE) \
			 || !memcmp(buf, K_CTRL_E, KEY_BUF_SIZE))
		move_end();
	else if (*buf && !*(buf + 1))
		insert(buf);
	else
		debug_buf(buf); //debug

	return (read_loop(buf));
}

t_bool	handle_pipe(char **line)
{
	char		buf;
	t_cursor	*c;

	switch_term();
	if (*line)
		ft_memdel((void *)line);
	c = get_cursor();
	if (tputs(tgetstr("u7", NULL), 0, tputs_output) == ERR)
        ;//     error(TPUTS, "nd"); 
	while (read(STDIN_FILENO, &buf, 1) > 0)
	{
		ft_laddlast(&c->first_l, ft_lnew((void *)&buf, 1));
		if (c->first_l && c->first_l->next 
			&& *(char *)c->first_l->content == '\e'
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
t_bool		read_stdin(char **line)
{
	t_cursor	*c;
	char		buf[KEY_BUF_SIZE + 1];

	switch_term();
	c = get_cursor();
    c->first_l = NULL;
    c->current_l = NULL;
	c->prompt_len = get_cursor_col() - 1;

	if (*line)
		ft_memdel((void *)line);

	if (read_loop(buf))
		*line = to_string();

	ft_lclean(&c->first_l);
	switch_term();
	return (*line ? TRUE : FALSE);
}
