/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 20:16:34 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/09 12:02:43 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_lst			*cp(t_lst *link)
{
	return (link);
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
		ft_lclean(&c->first_l);
	c->first_l = NULL;
	c->current_l = NULL;
}

t_cursor		*get_cursor(void)
{
	static t_cursor c = {0, 0, 0, 0, 0};

	return (&c);
}
