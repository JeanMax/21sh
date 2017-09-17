/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 18:19:56 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/17 18:13:00 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** command line history handling (mostly triggered with up/down keys)
*/

#include "line_edit.h"
#include <unistd.h>

static t_arr			**get_history_up(t_cursor *c, \
										t_arr **history, t_arr *line_save)
{
	if (c->line == line_save)
		c->line = *(t_arr **)c->history->ptr;
	else if ((size_t)(history + 1 - (t_arr **)c->history->ptr) \
			< c->history->length)
	{
		history++;
		c->line = *history;
	}
	return (history);
}

static t_arr			**get_history_down(t_cursor *c, t_arr **history, \
											t_arr *line_save)
{
	if (history != (t_arr **)c->history->ptr)
	{
		history--;
		c->line = *history;
	}
	else
		c->line = line_save;
	return (history);
}

static enum e_status	get_history_loop(char *buf, t_cursor *c, \
											t_arr **history, t_arr *line_save)
{
	print_line();
	move_end(NULL);
	ft_bzero(buf, KEY_BUF_SIZE + 1);
	if ((read(STDIN_FILENO, buf, KEY_BUF_SIZE)) < 0)
		return (KEEP_READING);
	move_begin(NULL);
	clear_line();
	if (!ft_memcmp(buf, K_UP, KEY_BUF_SIZE))
		history = get_history_up(c, history, line_save);
	else if (!ft_memcmp(buf, K_DOWN, KEY_BUF_SIZE))
		history = get_history_down(c, history, line_save);
	else
	{
		if (c->line != line_save)
		{
			ft_arrdel(&line_save);
			c->line = ft_arrdup(c->line);
		}
		print_line();
		move_end(NULL);
		return (do_stuff_with_key(buf));
	}
	return (get_history_loop(buf, c, history, line_save));
}

enum e_status			get_history(char *buf)
{
	t_cursor	*c;
	t_arr		*line_save;

	if (ft_memcmp(buf, K_UP, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->history->length)
		return (KEEP_READING);
	line_save = c->line;
	move_begin(NULL);
	clear_line();
	c->line = *(t_arr **)c->history->ptr;
	return (get_history_loop(buf, c, (t_arr **)c->history->ptr, line_save));
}
