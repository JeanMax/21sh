/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 10:02:01 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/23 17:15:06 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static t_bool			count_match(char *line, int *mis)
{
	if (!*line)
		return (TRUE);
	if (*line == '\'')
		mis[QUOTE]++;
	else if (*line == '"')
		mis[D_QUOTE]++;
	else if (*line == '`')
		mis[B_QUOTE]++;
	else if (*line == '[')
		mis[BRACKET]++;
	else if (*line == '{')
		mis[C_BRACKET]++;
	else if (*line == '(')
		mis[R_BRACKET]++;
	else if (*line == ']')
		mis[BRACKET]--;
	else if (*line == '}')
		mis[C_BRACKET]--;
	else if (*line == ')')
		mis[R_BRACKET]--;
	if (mis[BRACKET] < 0 || mis[C_BRACKET] < 0 || mis[R_BRACKET] < 0)
		return (FALSE);
	return (count_match(line + 1, mis));
}

static void				print_error(int *mis)
{
	move_end(NULL);
	ft_putendl("");
	if (mis[BRACKET])
		ft_putendl_clr(mis[BRACKET] > 0 ? \
					   "\tUnclosed [." : "\tUnclosed ].", CLR_RED);
	if (mis[C_BRACKET])
		ft_putendl_clr(mis[C_BRACKET] > 0 ? \
			"\tUnclosed {." : "\tUnclosed }.", CLR_RED);
	if (mis[R_BRACKET])
		ft_putendl_clr(mis[C_BRACKET] > 0 ? \
			"\tUnclosed (." : "\tUnclosed ).", CLR_RED);
	if (mis[QUOTE] % 2)
		ft_putendl_clr("\tMismatched '.", CLR_RED);
	if (mis[D_QUOTE] % 2)
		ft_putendl_clr("\tMismatched \".", CLR_RED);
	if (mis[B_QUOTE] % 2)
		ft_putendl_clr("\tMismatched `.", CLR_RED);
}

static t_bool			got_mismatch(char *line)
{
	int	mis[MIS_SIZE];

	ft_bzero(mis, MIS_SIZE * sizeof(int));
	if (!count_match(line, mis))
		return (TRUE);
	if (mis[BRACKET] || mis[C_BRACKET] || mis[R_BRACKET] \
			|| mis[QUOTE] % 2 || mis[D_QUOTE] % 2 || mis[B_QUOTE] % 2)
	{
		print_error(mis);
		return (TRUE);
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
