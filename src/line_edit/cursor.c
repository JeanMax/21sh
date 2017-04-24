/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 20:16:34 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/24 19:39:57 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void			clean_cursor(void)
{
	t_cursor *c;

	c = get_cursor();
/* 	if (!ft_lfind(&c->history, (void *)c->first_l, cmp)) */
/* 		ft_ldel(&c->first_l, free_char); */
/* 	c->first_l = NULL; */
/* 	c->current_l = NULL; */

	//TODO: wtf was that??
	ft_bzero(c->line->ptr, c->line->length);
	c->line->length = 0;
	c->current_length = 0;
}

static void		free_arr(void *arr, size_t n)
{
	(void)n;
	ft_arrdel(arr);
}

void			init_cursor(void)
{
	t_cursor	*c;

	c = get_cursor();
	c->line = ft_arrnew(LINE_SIZE, sizeof(char));
	c->save = ft_arrnew(0, sizeof(char));
	c->history = ft_arrnew(0, sizeof(t_arr *));
	c->history->del = free_arr;
}

void			finit_cursor(void)
{
	t_cursor	*c;

	c = get_cursor();
	ft_arrdel(&c->line);
	ft_arrdel(&c->save);
	ft_arrdel(&c->history);
}

t_cursor		*get_cursor(void)
{
	static t_cursor c = {0, 0, 0, 0, 0};

	return (&c);
}
