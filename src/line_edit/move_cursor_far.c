/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_far.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 17:28:15 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/24 15:17:24 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

enum e_status		move_begin(char *buf)
{
	t_cursor	*c;
	size_t		line_len;
	size_t		pos;

	if (buf && ft_memcmp(buf, K_START, KEY_BUF_SIZE) && \
		ft_memcmp(buf, K_CTRL_A, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_length || !c->line->length)
		return (KEEP_READING);
	pos = c->current_length + 1;
	c->current_length = 0;
	while (--pos)
	{
		line_len = get_term_size()->ws_col;
		if (!((pos + c->prompt_len) % line_len))
		{
			tputs(tgetstr("up", NULL), 0, tputs_output);
			while (line_len--)
				tputs(tgetstr("nd", NULL), 0, tputs_output);
		}
		else
			tputs(tgetstr("le", NULL), 0, tputs_output);
	}
	return (KEEP_READING);
}

enum e_status		move_end(char *buf)
{
	t_cursor	*c;
	size_t		pos;

	if (buf && ft_memcmp(buf, K_END, KEY_BUF_SIZE) \
		&& ft_memcmp(buf, K_CTRL_E, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->line->length)
		return (KEEP_READING);
	pos = c->current_length - 1;
	while (++pos < c->line->length)
	{
		if (!((pos + c->prompt_len + 1) % get_term_size()->ws_col))
		{
			tputs(tgetstr("do", NULL), 0, tputs_output);
			tputs(tgetstr("cr", NULL), 0, tputs_output);
		}
		else
			tputs(tgetstr("nd", NULL), 0, tputs_output);
	}
	c->current_length = c->line->length;
	return (KEEP_READING);
}

enum e_status		move_next_word(char *buf)
{
	t_cursor		*c;

	if (ft_memcmp(buf, K_CTRL_RIGHT, KEY_BUF_SIZE) \
		&& ft_memcmp(buf, K_ALT_F, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_length)
		move_right(NULL);
	while (c->current_length < c->line->length	\
		   && !ft_isspace(*((char *)c->line->ptr + c->current_length)))
		move_right(NULL);
	while (c->current_length < c->line->length	\
		   && ft_isspace(*((char *)c->line->ptr + c->current_length)))
		move_right(NULL);
	return (KEEP_READING);
}

enum e_status		move_prev_word(char *buf)
{
	t_cursor		*c;

	if (ft_memcmp(buf, K_CTRL_LEFT, KEY_BUF_SIZE) \
		&& ft_memcmp(buf, K_ALT_B, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_length)
		return (KEEP_READING);
	while (c->current_length \
		   && ft_isspace(*((char *)c->line->ptr + c->current_length - 1)))
		move_left(NULL);
	while (c->current_length \
		   && !ft_isspace(*((char *)c->line->ptr + c->current_length - 1)))
		move_left(NULL);
	return (KEEP_READING);
}
