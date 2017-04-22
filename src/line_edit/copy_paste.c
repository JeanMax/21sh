/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 17:24:57 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/22 13:51:58 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

enum e_status		copy(char *buf)
{
	t_cursor	*c;

	if (memcmp(buf, K_CTRL_P, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (c->save)
		ft_ldel(&c->save, free_char);
	c->save = ft_lmap(c->current_l ? c->current_l->next : c->first_l, cp);
	return (KEEP_READING);
}

enum e_status		cut_forward(char *buf)
{
	t_cursor	*c;

	if (memcmp(buf, K_CTRL_K, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_l && !c->first_l)
		return (KEEP_READING);
	clear_line();
	if (c->save)
		ft_ldel(&c->save, free_char);
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
	return (print_line());
}

enum e_status		cut_backward(char *buf)
{
	t_cursor	*c;
	t_lst		*current;

	if (memcmp(buf, K_CTRL_U, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->current_l || !c->first_l)
		return (KEEP_READING);
	if (c->save)
		ft_ldel(&c->save, free_char);
	current = c->current_l;
	move_begin(NULL);
	clear_line();
	c->save = c->first_l;
	if ((c->first_l = current->next))
		c->first_l->prev = NULL;
	c->current_l = NULL;
	current->next = NULL;
	print_line();
	return (KEEP_READING);
}

enum e_status		paste(char *buf)
{
	t_cursor	*c;
	t_lst		*last;
	t_lst		*cpy;
	size_t		len;

	if (memcmp(buf, K_CTRL_Y, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (!c->save || ft_llen(c->first_l) + ft_llen(c->save) >= LINE_SIZE)
		return (KEEP_READING);
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
		move_right(NULL);
	return (print_line());
}
