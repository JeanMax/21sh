/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:45:33 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 21:02:44 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	insert(char *s)
{
	t_cursor	*c;

	c = get_cursor();
	if (c->current_l)
		ft_linser(&(c->current_l), ft_lnew((void *)s, 1));
	else
		ft_ladd(&(c->first_l), ft_lnew((void *)s, 1));
	print_line();
	move_right();
}

void            del(void)
{
	t_cursor	*c;
	t_lst		*to_free;

	c = get_cursor();
	if (!c->current_l && !c->first_l)
		return ;
	if (!(to_free = c->current_l ? c->current_l->next : c->first_l))
		return ;

	if (to_free == c->first_l)
		c->first_l = c->first_l->next;
	ft_ldellink(to_free);
	ft_lfree(&to_free);
	print_line();
}

void            backspace(void)
{
	if (!get_cursor()->current_l)
		return ;
	move_left();
	del();
}

static t_lst	*cp(t_lst *link)
{
	return (link);
}

void			copy(void)
{
	t_cursor	*c;
	
	c = get_cursor();
	if (c->save)
		ft_lclean(&c->save);
	c->save = ft_lmap(c->current_l ? c->current_l->next : c->first_l, cp);
}

void			cut_forward(void)
{
	t_cursor	*c;
	
	c = get_cursor();
	if (!c->current_l && !c->first_l)
		return ;
	if (c->save)
		ft_lclean(&c->save);
	if (c->current_l)
	{
		c->save = c->current_l->next;
		if (c->save)
			c->save->prev = NULL;
		c->current_l->next = NULL;		
	}
	else
	{
		c->save = c->first_l;
		if (c->save)
			c->save->prev = NULL;
		c->first_l = NULL;		
	}
	print_line();
}

void			cut_backward(void)
{
	t_cursor	*c;
	t_lst		*current;
	
	c = get_cursor();
	if (!c->current_l || !c->first_l)
		return ;
	if (c->save)
		ft_lclean(&c->save);

	current = c->current_l;
	move_begin();
	c->save = c->first_l;
	if ((c->first_l = current->next))
		c->first_l->prev = NULL;
	c->current_l = NULL;
	current->next = NULL;

	print_line();
}

void			paste(void)
{
	t_cursor	*c;
	t_lst		*last;
	t_lst		*cpy;
	int			len;
	
	c = get_cursor();
	if (!c->save)
		return ;
	cpy = ft_lmap(c->save, cp);
	len = ft_llen(c->save);
	if (c->current_l)
		ft_linsert_list(c->current_l, cpy);
	else
	{
		last = ft_llast(cpy);
		last->next = c->first_l;
		if (c->first_l)
			c->first_l->prev = last;
		c->first_l = cpy;
	}
	while (len--)
		move_right();
	print_line();
}
