/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 18:19:56 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:50:26 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** command line history handling (mostly triggered with up/down keys)
*/

#include "line_edit.h"
#include <unistd.h>

static t_lst			*get_history_up(t_cursor *c, \
										t_lst *history, t_lst *line_save)
{
	if (c->first_l == line_save)
		c->first_l = (t_lst *)history->content;
	else if (history->next)
	{
		history = history->next;
		c->first_l = (t_lst *)history->content;
	}
	return (history);
}

static t_lst			*get_history_down(t_cursor *c, t_lst *history, \
											t_lst *line_save)
{
	if (history->prev)
	{
		history = history->prev;
		c->first_l = (t_lst *)history->content;
	}
	else
		c->first_l = line_save;
	return (history);
}

static enum e_status	get_history_loop(char *buf, t_cursor *c, \
											t_lst *history, t_lst *line_save)
{
	print_line();
	move_end(NULL);
	ft_bzero(buf, KEY_BUF_SIZE + 1);
	if ((read(STDIN_FILENO, buf, KEY_BUF_SIZE)) < 0)
		return (KEEP_READING);
	move_begin(NULL);
	clear_line();
	if (!memcmp(buf, K_UP, KEY_BUF_SIZE))
		history = get_history_up(c, history, line_save);
	else if (!memcmp(buf, K_DOWN, KEY_BUF_SIZE))
		history = get_history_down(c, history, line_save);
	else
	{
		if (c->first_l != line_save)
		{
			ft_ldel(&line_save, free_char);
			c->first_l = ft_lmap(c->first_l, cp);
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
	t_lst		*history;
	t_lst		*line_save;

	if (memcmp(buf, K_UP, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!(history = c->history))
		return (KEEP_READING);
	line_save = c->first_l;
	move_begin(NULL);
	clear_line();
	c->first_l = (t_lst *)history->content;
	return (get_history_loop(buf, c, history, line_save));
}
