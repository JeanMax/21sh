/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 18:19:56 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 04:25:16 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** command line history handling (mostly triggered with up/down keys)
*/

#include "flex_shell.h"

enum e_status		set_history(char *buf)
{
	t_cursor	*c;

	if (memcmp(buf, K_RETURN, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	if (c->first_l)
		ft_ladd(&c->history, ft_lnew((void *)c->first_l, sizeof(t_lst)));
	return (CMD_DONE);
}

enum e_status		get_history(char *buf)
{
	t_cursor	*c;
	t_lst		*history;
	t_lst		*line_save;

	if (memcmp(buf, K_UP, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	if (!(history = c->history))
		return (KEEP_READING);
	line_save = c->first_l;
	move_begin(NULL);
	c->first_l = (t_lst *)history->content;

	while (TRUE)
	{
		print_line(); //TODO: clear lines down
		ft_bzero(buf, KEY_BUF_SIZE + 1);
		if ((read(STDIN_FILENO, buf, KEY_BUF_SIZE)) < 0)
			return (KEEP_READING);

		if (!memcmp(buf, K_UP, KEY_BUF_SIZE))
		{
			if (c->first_l == line_save)
				c->first_l = (t_lst *)history->content;
			else if (history->next)
			{
				history = history->next;
				c->first_l = (t_lst *)history->content;
			}
		}
		else if (!memcmp(buf, K_DOWN, KEY_BUF_SIZE))
		{
			if (history->prev)
			{
				history = history->prev;
				c->first_l = (t_lst *)history->content;
			}
			else
				c->first_l = line_save;
		}
		else
		{
			if (c->first_l != line_save)
			{
				ft_lclean(&line_save);
				c->first_l = ft_lmap(c->first_l, cp);
			}
			return (do_stuff_with_key(buf));
		}
	}
	return (KEEP_READING); //coz clang's stupid
}
