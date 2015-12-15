/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 20:16:34 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/15 11:44:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

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

// < << <& > >> >& |
static void		assign_redirection(char **swap, t_lst **link)
{
	if (*(char *)((*link)->content) == '>')
	{
		if ((*link)->next && *(char *)((*link)->next->content) == '>' \
			&& (*link = (*link)->next))
			*((*swap)++) = R_OUTPUT_APPEND;
		else if ((*link)->next && *(char *)((*link)->next->content) == '&' \
				&& (*link = (*link)->next))
			*((*swap)++) = R_DUP_OUTPUT;
		else
			*((*swap)++) = R_OUTPUT;
	}
	else if (*(char *)((*link)->content) == '<')
	{
		if ((*link)->next && *(char *)((*link)->next->content) == '<' \
			&& (*link = (*link)->next))
			*((*swap)++) = R_HERE_DOC;
		else if ((*link)->next && *(char *)((*link)->next->content) == '&' \
				&& (*link = (*link)->next))
			*((*swap)++) = R_DUP_INPUT;
		else
			*((*swap)++) = R_INPUT;
	}
	else //if (*(char *)((*link)->content) == '|')
		*((*swap)++) = R_PIPELINE;
}

static void		assign(char **swap, t_lst **link, t_bool skip)
{
	if (skip)
	{
		*((*swap)++) = *(char *)((*link)->content);
		return ;
	}
	if (*(char *)((*link)->content) == '\n' || \
			*(char *)((*link)->content) == ';')
		*((*swap)++) = S_LINE;
	else if (ft_isspace(*(char *)((*link)->content)) || \
			*(char *)((*link)->content) == '\'' || \
			*(char *)((*link)->content) == '"')
		*((*swap)++) = S_WORD;
	else if (*(char *)((*link)->content) == '<' || \
			*(char *)((*link)->content) == '>' || \
			*(char *)((*link)->content) == '|')
	{
		//if it's a digit, you'll have to handle something like "3>"
		if (*(char *)((*link)->content) == '|' || ((*link)->prev && \
								!ft_isdigit(*(char *)((*link)->prev->content))))
			*((*swap)++) = S_WORD;
		assign_redirection(swap, link);
		*((*swap)++) = S_WORD;
	}
	else
		*((*swap)++) = *(char *)((*link)->content);
}

char			*to_string(void)
{
	static char	line[LINE_SIZE * 3 + 1];
	t_lst		*link;
	char		*swap;
	int			count;
	char		skip;

	link = get_cursor()->first_l;
	swap = line;
	ft_bzero(line, LINE_SIZE * 3 + 1);
	count = 0;
	skip = FALSE;
	while (count < LINE_SIZE && link)
	{
		if (skip == *(char *)(link->content))
		{
			skip = FALSE;
			assign(&swap, &link, skip);
		}
		else
		{
			assign(&swap, &link, skip);
			if (*(char *)(link->content) == '\'' || *(char *)(link->content) == '"')
				skip = *(char *)(link->content);
		}
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
			ft_putchar(' ');
		else if (!ft_isascii(*(char *)tmp->content) \
				|| ft_iscntrl(*(char *)tmp->content))
			ft_putstr("�");
		else
			ft_putchar(*(char *)tmp->content);
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
