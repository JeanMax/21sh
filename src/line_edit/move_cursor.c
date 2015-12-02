/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:19:41 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 20:58:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void move_up(void)
{
	t_cursor	*c;
	int			line_len;
	int			pos;
	int			keep_going;

	c = get_cursor();
	if (!c->current_l || !c->first_l)
		return ;

	pos = ft_lisn(c->first_l, c->current_l) + 1;
	keep_going = get_term_size()->ws_col + 1;
	while (--pos && --keep_going && c->current_l)
	{
		line_len = get_term_size()->ws_col;
		
		if (!((pos + c->prompt_len) % line_len))
		{
			if (tputs(tgetstr("up", NULL), 0, tputs_output) == ERR)
				;//		error(TPUTS, "le");
			while (line_len-- >= 0)
				if (tputs(tgetstr("nd", NULL), 0, tputs_output) == ERR)
					;//		error(TPUTS, "le");
		}
		else 
			if (tputs(tgetstr("le", NULL), 0, tputs_output) == ERR)
			;//		error(TPUTS, "le");		
		c->current_l = c->current_l->prev;
	}
}

void move_down(void)
{
	t_cursor	*c;
	int			pos;
	int			len;

	c = get_cursor();
	c->current_l = c->current_l ? c->current_l->next : c->first_l;
	pos = ft_lisn(c->first_l, c->current_l) + c->prompt_len - 1;
	len = get_term_size()->ws_col + pos;
	while (c->current_l && ++pos <= len)
	{
		if (!(pos % get_term_size()->ws_col))
		{
			if (tputs(tgetstr("do", NULL), 0, tputs_output) == ERR)
				;//		error(TPUTS, "le");
			if (tputs(tgetstr("cr", NULL), 0, tputs_output) == ERR)
				;//     error(TPUTS, "le"); 
		}
		else
			if (tputs(tgetstr("nd", NULL), 0, tputs_output) == ERR)
				;//		error(TPUTS, "le");
		c->current_l = c->current_l->next;
	}
	c->current_l = c->current_l ? c->current_l->prev : ft_llast(c->first_l);
}

void move_begin(void)
{
	t_cursor	*c;
	int			line_len;
	int			pos;

	c = get_cursor();
	if (!c->current_l || !c->first_l)
		return ;

	pos = ft_lisn(c->first_l, c->current_l) + 1;
	c->current_l = NULL;
	while (--pos)
	{
		line_len = get_term_size()->ws_col;
		
		if (!((pos + c->prompt_len) % line_len))
		{
			if (tputs(tgetstr("up", NULL), 0, tputs_output) == ERR)
				;//		error(TPUTS, "le");
			while (line_len-- >= 0)
				if (tputs(tgetstr("nd", NULL), 0, tputs_output) == ERR)
					;//		error(TPUTS, "le");
		}
		else 
			if (tputs(tgetstr("le", NULL), 0, tputs_output) == ERR)
			;//		error(TPUTS, "le");		
	}
}

void move_end(void)
{
	t_cursor	*c;
	int			pos;
	int			len;

	c = get_cursor();
	if (!c->first_l)
		return ;

	pos = ft_lisn(c->first_l, c->current_l) - 1;
	len = ft_llen(c->first_l);
	c->current_l = ft_llast(c->first_l);
	while (++pos < len)
	{
		if (!((pos + c->prompt_len + 1) % get_term_size()->ws_col))
		{
			if (tputs(tgetstr("do", NULL), 0, tputs_output) == ERR)
				;//		error(TPUTS, "le");
			if (tputs(tgetstr("cr", NULL), 0, tputs_output) == ERR)
				;//     error(TPUTS, "le"); 
		}
		else
			if (tputs(tgetstr("nd", NULL), 0, tputs_output) == ERR)
				;//		error(TPUTS, "le");
	}
}

void move_left(void)
{
	t_cursor	*c;
	int			line_len;

	c = get_cursor();
	if (!c->current_l || !c->first_l)
		return ;

	line_len = get_term_size()->ws_col;
	if (c->current_l != c->first_l && \
		!((ft_lisn(c->first_l, c->current_l) + c->prompt_len) % line_len))
	{
		if (tputs(tgetstr("up", NULL), 0, tputs_output) == ERR)
			;//		error(TPUTS, "le");
		while (line_len-- >= 0)
			if (tputs(tgetstr("nd", NULL), 0, tputs_output) == ERR)
				;//		error(TPUTS, "le");
	}
	else 
		if (tputs(tgetstr("le", NULL), 0, tputs_output) == ERR)
			;//		error(TPUTS, "le");		
	c->current_l = c->current_l->prev;
}

void move_right(void)
{
	t_cursor		*c;

	c = get_cursor();
	if (!c->current_l && c->first_l)
		c->current_l = c->first_l;
	else if (c->current_l && c->current_l->next)
		c->current_l = c->current_l->next;
	else
		return ;

	if (!((ft_lisn(c->first_l, c->current_l) + c->prompt_len) \
		  % get_term_size()->ws_col))
	{
		if (tputs(tgetstr("do", NULL), 0, tputs_output) == ERR)
			;//		error(TPUTS, "le");
		if (tputs(tgetstr("cr", NULL), 0, tputs_output) == ERR)
			;//     error(TPUTS, "le"); 
	}
	else
		if (tputs(tgetstr("nd", NULL), 0, tputs_output) == ERR)
			;//		error(TPUTS, "le");
}

void	move_next_word(void)
{
	t_cursor		*c;

	c = get_cursor();
	if (!c->current_l)
		move_right();
	while (c->current_l && c->current_l->next \
		   && !ft_isspace(*(char *)c->current_l->next->content))
		move_right();
	while (c->current_l && c->current_l->next \
		   && ft_isspace(*(char *)c->current_l->next->content))
		move_right();
}

void	move_prev_word(void)
{
	t_cursor		*c;

	c = get_cursor();
	if (!c->current_l)
		return ;
	while (c->current_l && ft_isspace(*(char *)c->current_l->content))
		move_left();
	while (c->current_l && !ft_isspace(*(char *)c->current_l->content))
		move_left();
}
