/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:32:59 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/17 18:11:37 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_bool			read_tty_brute(char **line)
{
	t_cursor	*c;
	char		buf[KEY_BUF_SIZE + 1];

	switch_term();
	c = get_cursor();
	c->prompt_len = (size_t)get_cursor_col() - 1;
	*line = read_loop(buf, KEEP_READING);
	ft_memcpy(*line, c->line->ptr, c->line->length);
	clean_cursor();
	switch_term();
	return (*line ? TRUE : FALSE);
}

t_bool			read_tty(char **line)
{
	t_cursor	*c;
	char		buf[KEY_BUF_SIZE + 1];

	switch_term();
	c = get_cursor();
	c->prompt_len = (size_t)get_cursor_col() - 1;
	*line = read_loop(buf, KEEP_READING);
	clean_cursor();
	switch_term();
	return (*line ? TRUE : FALSE);
}
