/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 10:02:01 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/14 16:48:21 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void				print_error(enum e_quote e)
{
	move_end(NULL);
	ft_putstr_clr("\n\tMismatched ", CLR_RED);
	ft_putendl_clr(e == QUOTE ? "'." : "\".", CLR_RED);
}

static t_bool			got_mismatch(char *line)
{
	char *quote;
	char *d_quote;
	enum e_quote e;

	quote = ft_strchr(line, QUOTE);
	if ((d_quote = ft_strchr(line, D_QUOTE)) && quote)
	{
		e = quote < d_quote ? QUOTE : D_QUOTE;
		line = MIN(quote, d_quote);
	}
	else
	{
		e = quote ? QUOTE : D_QUOTE;
		line = quote ? quote : d_quote;
	}
	if (line)
	{
		if (!(line = ft_strchr(line + 1, e)))
		{
			print_error(e);
			return (TRUE);
		}
		return (got_mismatch(line + 1));
	}
	return (FALSE);
}

enum e_status			set_history(char *buf)
{
	t_cursor	*c;

	if (ft_memcmp(buf, K_RETURN, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	c = get_cursor();
	if (got_mismatch((char *)c->line->ptr))
	{
		c->current_length = 0;
		c->prompt_len = 0;
		print_line();
		move_end(NULL);
		return (KEEP_READING);
	}
	if (c->line->length)
		ft_arrpush(c->history, ft_arrdup(c->line), 0);
	move_end(NULL);
	return (CMD_DONE);
}
