/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:44:23 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/24 16:59:43 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void				clear_line(void)
{
	char		*tmp;
	size_t		count;

	count = get_cursor()->prompt_len;
	tmp = (char *)get_cursor()->line->ptr;
	tputs(tgetstr("sc", NULL), 0, tputs_output);
	tputs(tgetstr("ce", NULL), 0, tputs_output);
	while (*tmp)
	{
		if (!(++count % get_term_size()->ws_col))
		{
			tputs(tgetstr("cd", NULL), 0, tputs_output);
			break ;
		}
		tmp++;
	}
	tputs(tgetstr("rc", NULL), 0, tputs_output);
}

enum e_status		clear_term(char *buf)
{
	t_cursor		*c;

	if (buf && ft_memcmp(buf, K_CTRL_L, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	move_begin(NULL);
	tputs(tgetstr("cl", NULL), 0, tputs_output);
	prompt();
	print_line();
	move_end(NULL);
	return (KEEP_READING);
}
