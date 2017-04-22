/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 20:16:34 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:49:49 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_lst			*cp(t_lst *link)
{
	return (link);
}

void			free_char(void *c, size_t n)
{
	(void)c;
	(void)n;
}

static int		cmp(const void *a, const void *b)
{
	return ((t_lst *)b != (t_lst *)((t_lst *)a)->content);
}

void			clean_cursor(void)
{
	t_cursor *c;

	c = get_cursor();
	if (!ft_lfind(&c->history, (void *)c->first_l, cmp))
		ft_ldel(&c->first_l, free_char);
	c->first_l = NULL;
	c->current_l = NULL;
}

t_cursor		*get_cursor(void)
{
	static t_cursor c = {0, 0, 0, 0, 0};

	return (&c);
}
