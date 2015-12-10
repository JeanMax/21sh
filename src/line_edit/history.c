/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 18:19:56 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 19:38:32 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** command line history handling (mostly triggered with up/down keys)
*/

#include "flex_shell.h"

static t_bool		got_mismatch(t_lst *link)
{
	int	quote; //TODO: array for norm?
	int	d_quote;
	int	b_quote;
	int	bracket;
	int	c_bracket;
	int	r_bracket;

	quote = 0;
	d_quote = 0;
	b_quote = 0;
	bracket = 0;
	c_bracket = 0;
	r_bracket = 0;
	while (link)
	{
		if (*(char *)link->content == '\'')
			quote++;
		else if (*(char *)link->content == '"')
			d_quote++;
		else if (*(char *)link->content == '`')
			b_quote++;
		else if (*(char *)link->content == '[')
			bracket++;
		else if (*(char *)link->content == '{')
			c_bracket++;
		else if (*(char *)link->content == '(')
			r_bracket++;
		else if (*(char *)link->content == ']')
			bracket--;
		else if (*(char *)link->content == '}')
			c_bracket--;
		else if (*(char *)link->content == ')')
			r_bracket--;

		if (bracket < 0 || c_bracket < 0 || r_bracket < 0) //can't be solved...
			return (TRUE);
		link = link->next;
	}

	if (bracket || c_bracket || r_bracket \
		|| quote % 2 || d_quote % 2 || b_quote % 2)
	{
		move_end(NULL);
		ft_putendl("");
		if (bracket)
			ft_putendl_clr(bracket > 0 ? "\tUnclosed [." : "\tUnclosed ].", "r");
		if (c_bracket)
			ft_putendl_clr(c_bracket > 0 ? "\tUnclosed {." : "\tUnclosed }.", "r");
		if (r_bracket)
			ft_putendl_clr(c_bracket > 0 ? "\tUnclosed (." : "\tUnclosed ).", "r");

		if (quote % 2)
			ft_putendl_clr("\tMismatched '.", "r");
		if (d_quote % 2)
			ft_putendl_clr("\tMismatched \".", "r");
		if (b_quote % 2)
			ft_putendl_clr("\tMismatched `.", "r");

		return (TRUE);
	}

	return (FALSE);
}

//TODO: rename? this is actually the 'return' function
enum e_status		set_history(char *buf)
{
	t_cursor	*c;

	if (memcmp(buf, K_RETURN, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	if (got_mismatch(c->first_l))
	{
		c->current_l = NULL;
		c->prompt_len = 0;
		print_line(); //cheated? :O
		move_end(NULL);
		return (KEEP_READING);
	}
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
	clear_line();
	c->first_l = (t_lst *)history->content;

	while (TRUE)
	{
		print_line();
		move_end(NULL);
		ft_bzero(buf, KEY_BUF_SIZE + 1);
		if ((read(STDIN_FILENO, buf, KEY_BUF_SIZE)) < 0)
			return (KEEP_READING);
		move_begin(NULL);
		clear_line();
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
			print_line();
			move_end(NULL);
			return (do_stuff_with_key(buf));
		}
	}
	return (KEEP_READING); //coz clang's stupid
}
