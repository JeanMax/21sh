/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:57:47 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 17:20:57 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void		print_line_loop(t_lst *tmp, size_t count)
{
	while (tmp)
	{
		if (ft_isspace(*(char *)tmp->content))
			ft_putchar(' ');
		else if (!ft_isascii(*(char *)tmp->content) \
				|| ft_iscntrl(*(char *)tmp->content))
			ft_putstr("�");
		else
			ft_putchar(*(char *)tmp->content);
		if (!(++count % get_term_size()->ws_col))
		{
			tputs(tgetstr("cd", NULL), 0, tputs_output);
			ft_putendl("");
		}
		tmp = tmp->next;
	}
}

enum e_status	print_line(void)
{
	t_cursor	*c;
	t_lst		*current;

	c = get_cursor();
	current = c->current_l;
	move_begin(NULL);
	tputs(tgetstr("ce", NULL), 0, tputs_output);
	print_line_loop(c->first_l, c->prompt_len);
	c->current_l = ft_llast(c->first_l);
	while (c->current_l != current)
		move_left(NULL);
	return (KEEP_READING);
}
