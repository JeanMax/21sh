/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 20:16:34 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 22:35:48 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flex_shell.h"

void			clean_cursor(void)
{
	t_cursor *c;

	c = get_cursor();
	ft_lclean(&c->first_l);
	c->first_l = NULL;
	c->current_l = NULL;
}

t_cursor		*get_cursor(void)
{
	static t_cursor c = {0, 0, 0, 0, 0};

	return (&c);
}

char			*to_string(void)
{
	static char	line[LINE_SIZE + 1];
	t_lst	*link;
	char	*swap;
	int		count;

	link = get_cursor()->first_l;
	swap = line;
	ft_bzero(line, LINE_SIZE);
	count = 0;
	while (count < LINE_SIZE && link)
	{
		if (*(char *)(link->content) == '\n')
			*(swap++) = ';';
		else
			*(swap++) = *(char *)(link->content);
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
