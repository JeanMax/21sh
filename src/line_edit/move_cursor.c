/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:19:41 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 17:39:58 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

enum e_status		move_up(char *buf)
{
	t_cursor	*c;
	size_t		line_len;
	size_t		pos;
	size_t		keep_going;

	if (memcmp(buf, K_CTRL_UP, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_l || !c->first_l)
		return (KEEP_READING);
	pos = ft_lisn(c->first_l, c->current_l) + 1;
	keep_going = get_term_size()->ws_col + 1;
	while (--pos && --keep_going && c->current_l)
	{
		line_len = get_term_size()->ws_col;
		if (!((pos + c->prompt_len) % line_len) \
				&& tputs(tgetstr("up", NULL), 0, tputs_output) != -1)
			while (line_len--)
				tputs(tgetstr("nd", NULL), 0, tputs_output);
		else
			tputs(tgetstr("le", NULL), 0, tputs_output);
		c->current_l = c->current_l->prev;
	}
	return (KEEP_READING);
}

enum e_status		move_down(char *buf)
{
	t_cursor	*c;
	size_t		pos;
	size_t		len;

	if (memcmp(buf, K_CTRL_DOWN, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	c->current_l = c->current_l ? c->current_l->next : c->first_l;
	pos = ft_lisn(c->first_l, c->current_l) + c->prompt_len - 1;
	len = get_term_size()->ws_col + pos;
	while (c->current_l && ++pos <= len)
	{
		if (!(pos % get_term_size()->ws_col))
		{
			tputs(tgetstr("do", NULL), 0, tputs_output);
			tputs(tgetstr("cr", NULL), 0, tputs_output);
		}
		else
			tputs(tgetstr("nd", NULL), 0, tputs_output);
		c->current_l = c->current_l->next;
	}
	c->current_l = c->current_l ? c->current_l->prev : ft_llast(c->first_l);
	return (KEEP_READING);
}

enum e_status		move_left(char *buf)
{
	t_cursor	*c;
	size_t		line_len;

	if (buf && memcmp(buf, K_LEFT, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	if (!c->current_l || !c->first_l)
		return (KEEP_READING);

	line_len = get_term_size()->ws_col;
	if (c->current_l != c->first_l && \
		!((ft_lisn(c->first_l, c->current_l) + c->prompt_len) % line_len))
	{
		tputs(tgetstr("up", NULL), 0, tputs_output);
		while (line_len--)
			tputs(tgetstr("nd", NULL), 0, tputs_output);
	}
	else
		tputs(tgetstr("le", NULL), 0, tputs_output);
	c->current_l = c->current_l->prev;
	return (KEEP_READING);
}

enum e_status		move_right(char *buf)
{
	t_cursor		*c;

	if (buf && memcmp(buf, K_RIGHT, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	if (!c->current_l && c->first_l)
		c->current_l = c->first_l;
	else if (c->current_l && c->current_l->next)
		c->current_l = c->current_l->next;
	else
		return (KEEP_READING);

	if (!((ft_lisn(c->first_l, c->current_l) + c->prompt_len) \
			% get_term_size()->ws_col))
	{
		tputs(tgetstr("do", NULL), 0, tputs_output);
		tputs(tgetstr("cr", NULL), 0, tputs_output);
	}
	else
		tputs(tgetstr("nd", NULL), 0, tputs_output);
	return (KEEP_READING);
}
