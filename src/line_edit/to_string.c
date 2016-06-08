/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:58:45 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 16:59:05 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

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
	else
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
		if (*(char *)((*link)->content) == '|' || ((*link)->prev && \
								!ft_isdigit(*(char *)((*link)->prev->content))))
			*((*swap)++) = S_WORD;
		assign_redirection(swap, link);
		*((*swap)++) = S_WORD;
	}
	else
		*((*swap)++) = *(char *)((*link)->content);
}

static void		to_string_loop(char *swap, t_lst *link)
{
	int			count;
	char		skip;

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
			if (*(char *)(link->content) == '\'' \
					|| *(char *)(link->content) == '"')
				skip = *(char *)(link->content);
		}
		link = link->next;
		count++;
	}
	*swap = 0;
}

char			*to_string(void)
{
	static char	line[LINE_SIZE * 3 + 1];

	ft_bzero(line, LINE_SIZE * 3 + 1);
	to_string_loop(line, get_cursor()->first_l);
	return (line);
}
