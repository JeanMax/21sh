/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:19:41 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 22:39:10 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flex_shell.h"

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
		if (!((pos + c->prompt_len) % line_len))
		{
			tputs(tgetstr("up", NULL), 0, tputs_output);
			while (line_len--)
				tputs(tgetstr("nd", NULL), 0, tputs_output);
		}
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
