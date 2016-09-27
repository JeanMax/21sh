/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:58:39 by mcanal            #+#    #+#             */
/*   Updated: 2016/09/27 21:40:16 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include <unistd.h>

static void		*get_f_array(void)
{
	static enum e_status	(*f[])(char *) = {
		clear_term,
		del,
		backspace,
		copy,
		cut_forward,
		cut_backward,
		paste,
		move_left,
		move_right,
		move_up,
		move_down,
		move_begin,
		move_end,
		move_next_word,
		move_prev_word,
		set_history,
		get_history,
		insert,
		NULL
	};

	return ((void *)f);
}

enum e_status	do_stuff_with_key(char *buf)
{
	enum e_status	status;
	enum e_status	(**f)(char *);

	status = KEEP_TRYING;
	f = get_f_array();
	while (*f && status == KEEP_TRYING)
		status = (*(f++))(buf);
	return (status);
}

char			*read_loop(char *buf, enum e_status status)
{
	ft_bzero(buf, KEY_BUF_SIZE + 1);
	if (status == CMD_DONE)
		return (to_string());
	if (status == STOP_READING || (read(STDIN_FILENO, buf, KEY_BUF_SIZE)) < 0)
		return (NULL);
	return (read_loop(buf, do_stuff_with_key(buf)));
}
