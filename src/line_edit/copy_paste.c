/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 17:24:57 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/24 18:09:34 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

enum e_status		copy(char *buf)
{
	t_cursor	*c;

	if (ft_memcmp(buf, K_CTRL_P, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (c->save)
		ft_arrdel(&c->save);
	c->save = ft_arrdup(c->line);
	move_end(NULL);
	return (KEEP_READING);
}

enum e_status		cut_forward(char *buf)
{
	t_cursor	*c;

	if (ft_memcmp(buf, K_CTRL_K, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (c->current_length && !c->line->length)
		return (KEEP_READING);
	clear_line();
	if (c->save)
		ft_arrdel(&c->save);
	c->save = ft_arrdup(c->line);
	if (c->current_length)
	{
		ft_arrslice(c->save, (int)c->current_length, -1, -1);
		ft_arrslice(c->line, 0, (int)c->current_length - 1, 1);
	}
	else
	{
		ft_arrslice(c->save, 0, -1, -1);
		ft_bzero(c->line->ptr, c->line->length);
		c->line->length = 0;
	}
	return (print_line());
}

enum e_status		cut_backward(char *buf)
{
	t_cursor	*c;

	if (ft_memcmp(buf, K_CTRL_U, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_length || !c->line->length)
		return (KEEP_READING);
	clear_line();
	if (c->save)
		ft_arrdel(&c->save);
	c->save = ft_arrdup(c->line);
	if (c->current_length != c->line->length)
	{
		ft_arrslice(c->save, 0, (int)c->current_length - 1, -1);
		ft_arrslice(c->line, (int)c->current_length, -1, 1);
	}
	else
	{
		move_begin(NULL);
		ft_arrslice(c->save, 0, -1, -1);
		ft_bzero(c->line->ptr, c->line->length);
		c->line->length = 0;
	}
	move_begin(NULL);
	return (print_line());
}

enum e_status		paste(char *buf)
{
	t_cursor	*c;
	size_t		len;
	char		*swap;

	if (ft_memcmp(buf, K_CTRL_Y, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->save || c->line->length + c->save->length >= LINE_SIZE)
		return (KEEP_READING);
	swap = (char *)c->save->ptr;
	while (*swap)
		ft_arrpush(c->line, (void *)(long)*swap++, (int)c->current_length);
	len = c->save->length;
	while (len--)
		move_right(NULL);
	return (print_line());
}
