/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:19:41 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/24 16:03:42 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

enum e_status		move_up(char *buf)
{
	t_cursor	*c;
	size_t	line_len;

	if (ft_memcmp(buf, K_CTRL_UP, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_length || !c->line->length)
		return (KEEP_READING);
	line_len = get_term_size()->ws_col + 1;
	while (--line_len)
		move_left(NULL);
	return (KEEP_READING);
}

enum e_status		move_down(char *buf)
{
	t_cursor	*c;
	size_t		line_len;

	if (ft_memcmp(buf, K_CTRL_DOWN, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->line->length || c->current_length == c->line->length)
		return (KEEP_READING);
	line_len = get_term_size()->ws_col + 1;
	while (--line_len)
		move_right(NULL);
	return (KEEP_READING);
}

enum e_status		move_left(char *buf)
{
	t_cursor	*c;
	size_t		line_len;

	if (buf && ft_memcmp(buf, K_LEFT, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_length || !c->line->length)
		return (KEEP_READING);
	line_len = get_term_size()->ws_col;
	if (!((c->current_length + c->prompt_len) % line_len))
	{
		tputs(tgetstr("up", NULL), 0, tputs_output);
		while (line_len--)
			tputs(tgetstr("nd", NULL), 0, tputs_output);
	}
	else
		tputs(tgetstr("le", NULL), 0, tputs_output);
	c->current_length--;
	return (KEEP_READING);
}

enum e_status		move_right(char *buf)
{
	t_cursor		*c;

	if (buf && ft_memcmp(buf, K_RIGHT, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (c->current_length < c->line->length)
		c->current_length++;
	else
		return (KEEP_READING);
	if (!((c->current_length + c->prompt_len) % get_term_size()->ws_col))
	{
		tputs(tgetstr("do", NULL), 0, tputs_output);
		tputs(tgetstr("cr", NULL), 0, tputs_output);
	}
	else
		tputs(tgetstr("nd", NULL), 0, tputs_output);
	return (KEEP_READING);
}
