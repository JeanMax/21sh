/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_notty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:34:22 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 16:34:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_bool			read_notty_brute(char **line)
{
	ft_memdel((void *)line);
	if (get_next_line(STDIN_FILENO, line) != 1)
		return (FALSE);
	return (*line ? TRUE : FALSE);
}

t_bool			read_notty(char **line)
{
	char		*swap;
	t_cursor	*c;

	c = get_cursor();
	if (get_next_line(STDIN_FILENO, line) != 1)
		return (FALSE);
	if ((swap = *line))
		while (*swap)
			ft_laddlast(&c->first_l, ft_lnew((void *)swap++, 1));
	ft_memdel((void *)line);
	*line = to_string();
	ft_lclean(&c->first_l);
	return (*line ? TRUE : FALSE);
}
