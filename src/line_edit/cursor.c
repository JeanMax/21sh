/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 20:16:34 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 21:21:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		clean_cursor(void)
{
	t_cursor *c;

	c = get_cursor();
	ft_lclean(&c->first_l);
	c->first_l = NULL;
	c->current_l = NULL;
}

t_cursor	*get_cursor(void)
{
	static t_cursor c = {0, 0, 0, 0};

	return (&c);
}

char	*to_string(void)
{
	t_lst	*link;
	char	*s;
	char	*swap;

	link = get_cursor()->first_l;
	if (!(s = (char *)malloc(sizeof(char) * (ft_llen(link) + 1))))
		return (NULL);
	swap = s;
	while (link)
	{
		if (*(char *)(link->content) == '\n')
			*(s++) = ';';
		else
			*(s++) = *(char *)(link->content);
		link = link->next;
	}
	*s = 0;
	return (swap);
}

void print_line(void)
{
	t_cursor	*c;
	t_lst		*current;
	t_lst		*tmp;
	int			count;

	c = get_cursor();
	current = c->current_l;
	move_begin();

	if (tputs(tgetstr("ce", NULL), 0, tputs_output) == ERR)
		;//     error(TPUTS, "le");    

	count = c->prompt_len;
	tmp = c->first_l;
	while (tmp)
	{
		write(1, tmp->content, 1);
		if (!(++count % get_term_size()->ws_col))
		{
			if (tputs(tgetstr("cd", NULL), 0, tputs_output) == ERR)
				;//     error(TPUTS, "le");    
			ft_putendl("");
		}
		tmp = tmp->next;
	}

	c->current_l = ft_llast(c->first_l);
	while (c->current_l != current)
		move_left();
}

