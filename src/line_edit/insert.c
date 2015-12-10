/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:45:33 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 22:36:07 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flex_shell.h"

enum e_status		insert(char *buf)
{
	t_cursor	*c;

	if (!*buf || *(buf + 1))
		return (KEEP_TRYING);

	c = get_cursor();
	if (ft_llen(c->first_l) + 1 >= LINE_SIZE)
		return (KEEP_READING);
	if (c->current_l)
		ft_linser(&(c->current_l), ft_lnew(buf, 1));
	else
		ft_ladd(&(c->first_l), ft_lnew(buf, 1));
	print_line();
	move_right(NULL);
	return (KEEP_READING);
}

enum e_status		del(char *buf)
{
	t_cursor	*c;
	t_lst		*to_free;

	if (buf && !memcmp(buf, K_CTRL_D, KEY_BUF_SIZE))
	{
		if (!get_cursor()->first_l)
			return (STOP_READING);
	}
	else if (buf && memcmp(buf, K_DEL, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	if (!c->current_l && !c->first_l)
		return (KEEP_READING);
	if (!(to_free = c->current_l ? c->current_l->next : c->first_l))
		return (KEEP_READING);

	if (to_free == c->first_l)
		c->first_l = c->first_l->next;
	ft_ldellink(to_free);
	ft_lfree(&to_free);
	print_line();
	return (KEEP_READING);
}

enum e_status		backspace(char *buf)
{
	if (memcmp(buf, K_BACKSPACE, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	if (!get_cursor()->current_l)
		return (KEEP_READING);
	move_left(NULL);
	del(NULL);
	return (KEEP_READING);
}

t_lst			*cp(t_lst *link) //TODO: move
{
	return (link);
}

enum e_status		copy(char *buf)
{
	t_cursor	*c;

	if (memcmp(buf, K_CTRL_P, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (c->save)
		ft_lclean(&c->save);
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
	return (KEEP_READING);
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
		ft_lclean(&c->save);

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
	print_line();
	return (KEEP_READING);
}
