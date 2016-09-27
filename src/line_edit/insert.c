/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:45:33 by mcanal            #+#    #+#             */
/*   Updated: 2016/09/27 21:31:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

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
