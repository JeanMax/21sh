/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:45:33 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/16 23:14:34 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

enum e_status		insert(char *buf)
{
	t_cursor	*c;

	if (!*buf || *(buf + 1))
		return (KEEP_TRYING);
	c = get_cursor();
	if (c->line->length + 1 >= LINE_SIZE)
		return (KEEP_READING);
	ft_arrpush(c->line, (void *)(long)*buf, (int)c->current_length);
	print_line();
	move_right(NULL);
	return (KEEP_READING);
}

enum e_status		del(char *buf)
{
	t_cursor	*c;

	if (buf && !ft_memcmp(buf, K_CTRL_D, KEY_BUF_SIZE))
	{
		if (!get_cursor()->line->length)
			return (STOP_READING);
	}
	else if (buf && ft_memcmp(buf, K_DEL, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->line->length || c->current_length == c->line->length)
		return (KEEP_READING);
	ft_arrpop(c->line, (int)c->current_length);
	print_line();
	return (KEEP_READING);
}

enum e_status		backspace(char *buf)
{
	if (ft_memcmp(buf, K_BACKSPACE, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	if (!get_cursor()->current_length)
		return (KEEP_READING);
	move_left(NULL);
	del(NULL);
	return (KEEP_READING);
}
