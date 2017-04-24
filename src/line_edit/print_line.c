/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:57:47 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/24 17:09:46 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void		print_line_loop(char *line, size_t count)
{
	while (*line)
	{
		if (ft_isspace(*line))
			ft_putchar(' ');
		else if (!ft_isascii(*line) || ft_iscntrl(*line))
			ft_putstr("�"); //TODO: pieg
		else
			ft_putchar(*line);
		if (!(++count % get_term_size()->ws_col))
		{
			tputs(tgetstr("cd", NULL), 0, tputs_output);
			ft_putchar('\n');
		}
		line++;
	}
}

enum e_status	print_line(void)
{
	t_cursor	*c;
	size_t	current_length;

	c = get_cursor();
	current_length = c->current_length;
	move_begin(NULL);
	tputs(tgetstr("ce", NULL), 0, tputs_output);
	if (c->line->length)
	{
		print_line_loop((char *)c->line->ptr, c->prompt_len);
		c->current_length = c->line->length;
		while (c->current_length != current_length)
			move_left(NULL);
	}
	return (KEEP_READING);
}
