/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:32:59 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:51:03 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_bool			read_tty_brute(char **line)
{
	t_cursor	*c;
	char		buf[KEY_BUF_SIZE + 1];
	char		*swap;

	switch_term();
	c = get_cursor();
	c->current_l = NULL;
	c->prompt_len = (size_t)get_cursor_col() - 1;
	if (!(*line = read_loop(buf, KEEP_READING)))
		ft_ldel(&c->first_l, free_char);
	swap = *line;
	while (*swap && c->first_l)
	{
		*(swap++) = *(char *)(c->first_l->content);
		c->first_l = c->first_l->next;
	}
	*swap = 0;
	c->first_l = NULL;
	switch_term();
	return (*line ? TRUE : FALSE);
}

t_bool			read_tty(char **line)
{
	t_cursor	*c;
	char		buf[KEY_BUF_SIZE + 1];

	switch_term();
	c = get_cursor();
	c->current_l = NULL;
	c->prompt_len = (size_t)get_cursor_col() - 1;
	if (!(*line = read_loop(buf, KEEP_READING)))
		ft_ldel(&c->first_l, free_char);
	c->first_l = NULL;
	switch_term();
	return (*line ? TRUE : FALSE);
}
