/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 10:02:01 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/09 11:16:58 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

enum		e_mismatch
{
	QUOTE = 0,
	D_QUOTE = 1,
	B_QUOTE = 2,
	BRACKET = 3,
	C_BRACKET = 4,
	R_BRACKET = 5,
	MIS_SIZE = 6
};

static t_bool			count_match(t_lst *link, int *mis)
{
	if (!link)
		return (TRUE);
	if (*(char *)link->content == '\'')
		mis[QUOTE]++;
	else if (*(char *)link->content == '"')
		mis[D_QUOTE]++;
	else if (*(char *)link->content == '`')
		mis[B_QUOTE]++;
	else if (*(char *)link->content == '[')
		mis[BRACKET]++;
	else if (*(char *)link->content == '{')
		mis[C_BRACKET]++;
	else if (*(char *)link->content == '(')
		mis[R_BRACKET]++;
	else if (*(char *)link->content == ']')
		mis[BRACKET]--;
	else if (*(char *)link->content == '}')
		mis[C_BRACKET]--;
	else if (*(char *)link->content == ')')
		mis[R_BRACKET]--;
	if (mis[BRACKET] < 0 || mis[C_BRACKET] < 0 || mis[R_BRACKET] < 0)
		return (FALSE);
	return (count_match(link->next, mis));
}

static void				print_error(int *mis)
{
	move_end(NULL);
	ft_putendl("");
	if (mis[BRACKET])
		ft_putendl_clr(mis[BRACKET] > 0 ? \
			"\tUnclosed [." : "\tUnclosed ].", "r");
	if (mis[C_BRACKET])
		ft_putendl_clr(mis[C_BRACKET] > 0 ? \
			"\tUnclosed {." : "\tUnclosed }.", "r");
	if (mis[R_BRACKET])
		ft_putendl_clr(mis[C_BRACKET] > 0 ? \
			"\tUnclosed (." : "\tUnclosed ).", "r");
	if (mis[QUOTE] % 2)
		ft_putendl_clr("\tMismatched '.", "r");
	if (mis[D_QUOTE] % 2)
		ft_putendl_clr("\tMismatched \".", "r");
	if (mis[B_QUOTE] % 2)
		ft_putendl_clr("\tMismatched `.", "r");
}

//TODO: check the to_string instead
static t_bool			got_mismatch(t_lst *link)
{
	int	mis[MIS_SIZE] = {0, 0, 0, 0, 0, 0};

	if (!count_match(link, mis))
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

	if (memcmp(buf, K_RETURN, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	if (got_mismatch(c->first_l))
	{
		c->current_l = NULL;
		c->prompt_len = 0;
		print_line();
		move_end(NULL);
		return (KEEP_READING);
	}
	if (c->first_l)
		ft_ladd(&c->history, ft_lnew((void *)c->first_l, sizeof(t_lst)));
	return (CMD_DONE);
}
