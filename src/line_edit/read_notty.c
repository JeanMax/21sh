/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_notty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:34:22 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/24 19:38:24 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_bool			read_notty_brute(char **line)
{
	ft_memdel((void *)line);
	if (get_next_line(STDIN_FILENO, line) <= 0)
		return (FALSE);
	return (*line ? TRUE : FALSE);
}

t_bool			read_notty(char **line)
{
	char		*swap;
	t_cursor	*c;

	c = get_cursor();
	if (get_next_line(STDIN_FILENO, line) <= 0)
		return (FALSE);
	if ((swap = *line))
		while (*swap)
			ft_arrpush(c->line, (void *)(long)*swap++, -1);
	ft_memdel((void *)line);
	*line = to_string();
	clean_cursor(); //TODO: no idea what I'm doing
	return (*line ? TRUE : FALSE);
}
