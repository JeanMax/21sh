/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_far.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 17:28:15 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 17:31:31 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

enum e_status		move_begin(char *buf)
{
	t_cursor	*c;
	size_t		line_len;
	size_t		pos;

	if (buf && memcmp(buf, K_START, KEY_BUF_SIZE) && \
		memcmp(buf, K_CTRL_A, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_l || !c->first_l)
		return (KEEP_READING);
	pos = ft_lisn(c->first_l, c->current_l) + 1;
	c->current_l = NULL;
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
	size_t		len;

	if (buf && memcmp(buf, K_END, KEY_BUF_SIZE) \
		&& memcmp(buf, K_CTRL_E, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->first_l)
		return (KEEP_READING);
	pos = ft_lisn(c->first_l, c->current_l) - 1;
	len = ft_llen(c->first_l);
	c->current_l = ft_llast(c->first_l);
	while (++pos < len)
	{
		if (!((pos + c->prompt_len + 1) % get_term_size()->ws_col))
		{
			tputs(tgetstr("do", NULL), 0, tputs_output);
			tputs(tgetstr("cr", NULL), 0, tputs_output);
		}
		else
			tputs(tgetstr("nd", NULL), 0, tputs_output);
	}
	return (KEEP_READING);
}

enum e_status		move_next_word(char *buf)
{
	t_cursor		*c;

	if (memcmp(buf, K_CTRL_RIGHT, KEY_BUF_SIZE) \
		&& memcmp(buf, K_ALT_F, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_l)
		move_right(NULL);
	while (c->current_l && c->current_l->next \
			&& !ft_isspace(*(char *)c->current_l->next->content))
		move_right(NULL);
	while (c->current_l && c->current_l->next \
			&& ft_isspace(*(char *)c->current_l->next->content))
		move_right(NULL);
	return (KEEP_READING);
}

enum e_status		move_prev_word(char *buf)
{
	t_cursor		*c;

	if (memcmp(buf, K_CTRL_LEFT, KEY_BUF_SIZE) \
		&& memcmp(buf, K_ALT_B, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_l)
		return (KEEP_READING);
	while (c->current_l && ft_isspace(*(char *)c->current_l->content))
		move_left(NULL);
	while (c->current_l && !ft_isspace(*(char *)c->current_l->content))
		move_left(NULL);
	return (KEEP_READING);
}
