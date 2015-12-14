/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 20:16:34 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 03:20:20 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flex_shell.h"

static int		cmp(const void *a, const void *b)
{
	return ((t_lst *)b != (t_lst *)((t_lst *)a)->content);
}
void			clean_cursor(void)
{
	t_cursor *c;

	c = get_cursor();
	if (!ft_lfind(&c->history, (void *)c->first_l, cmp))
		ft_lclean(&c->first_l);
	c->first_l = NULL;
	c->current_l = NULL;
}

t_cursor		*get_cursor(void)
{
	static t_cursor c = {0, 0, 0, 0, 0};

	return (&c);
}

static char		assign(char to_add, t_bool skip)
{
	if (!skip)
	{
		if (to_add == '\n' || to_add == ';')
			return (S_LINE);
		if (ft_isspace((int)to_add) || to_add == '\'' || to_add == '"')
			return (S_WORD);
	}
	return (to_add);
}

char			*to_string(void)
{
	static char	line[LINE_SIZE + 1];
	t_lst		*link;
	char		*swap;
	int			count;
	char		skip;

	link = get_cursor()->first_l;
	swap = line;
	ft_bzero(line, LINE_SIZE);
	count = 0;
	skip = FALSE;
	while (count < LINE_SIZE && link)
	{
		if (skip == *(char *)(link->content))
			skip = FALSE;
		*(swap++) = assign(*(char *)(link->content), skip);
		if (*(char *)(link->content) == '\'' || *(char *)(link->content) == '"')
			skip = *(char *)(link->content);
		link = link->next;
		count++;
	}
	*swap = 0;
	return (line);
}

void			print_line(void)
{
	t_cursor	*c;
	t_lst		*current;
	t_lst		*tmp;
	size_t		count;

	c = get_cursor();
	current = c->current_l;
	move_begin(NULL);

	tputs(tgetstr("ce", NULL), 0, tputs_output);

	count = c->prompt_len;
	tmp = c->first_l;
	while (tmp)
	{
		if (ft_isspace(*(char *)tmp->content))
			write(1, " ", 1);
		else if (!ft_isascii(*(char *)tmp->content) \
				|| ft_iscntrl(*(char *)tmp->content))
			ft_putstr("�");
		else
			write(1, tmp->content, 1);
		if (!(++count % get_term_size()->ws_col))
		{
			tputs(tgetstr("cd", NULL), 0, tputs_output);
			ft_putendl("");
		}
		tmp = tmp->next;
	}

	c->current_l = ft_llast(c->first_l);
	while (c->current_l != current)
		move_left(NULL);
}
