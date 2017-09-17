/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 10:02:01 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/17 18:26:40 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static enum e_quote		got_mismatch(char *line)
{
	char			*quote;
	char			*d_quote;
	enum e_quote	e;

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
			return (e);
		return (got_mismatch(line + 1));
	}
	return (NOP);
}

static void				relou(t_arr *all_lines, enum e_quote e)
{
	clean_cursor();
	ft_arrpush(all_lines, (void *)(long)'\n', -1);
	ft_putstr(e == QUOTE ? "\nquote> " : "\ndquote> ");
	move_end(NULL);
}

enum e_status			set_history(char *buf)
{
	t_cursor		*c;
	char			*s;
	enum e_quote	e;
	static t_arr	*all_lines = NULL;

	if (ft_memcmp(buf, K_RETURN, KEY_BUF_SIZE))
		return (KEEP_TRYING);
	if (!all_lines)
		all_lines = ft_arrnew(LINE_SIZE, sizeof(char));
	c = get_cursor();
	s = (char *)c->line->ptr;
	while (*s)
		ft_arrpush(all_lines, (void *)(long)*s++, -1);
	if ((e = got_mismatch(all_lines->ptr)))
	{
		relou();
		return (KEEP_READING);
	}
	ft_arrdel(&c->line);
	c->line = all_lines;
	all_lines = NULL;
	if (c->line->length)
		ft_arrpush(c->history, ft_arrdup(c->line), 0);
	move_end(NULL);
	return (CMD_DONE);
}
