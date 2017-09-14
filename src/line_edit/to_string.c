/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:58:45 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/12 22:22:10 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TODO: rewrite that shit
*/

#include "line_edit.h"

static void		assign_redirection(char **str, char **line)
{
	if (**line == '>')
	{
		if (*((*line) + 1) == '>' && *++(*line))
			*((*str)++) = R_OUTPUT_APPEND;
		else if (*((*line) + 1) == '&' && *++(*line))
			*((*str)++) = R_DUP_OUTPUT;
		else
			*((*str)++) = R_OUTPUT;
	}
	else if (**line == '<')
	{
		if (*((*line) + 1) == '<' && *++(*line))
			*((*str)++) = R_HERE_DOC;
		else if (*((*line) + 1) == '&' && *++(*line))
			*((*str)++) = R_DUP_INPUT;
		else
			*((*str)++) = R_INPUT;
	}
	else
		*((*str)++) = R_PIPELINE;
}

// TODO: the "/' handling is bugged
static void		assign(char **str, char **line, t_bool skip)
{
	if (skip)
	{
		*((*str)++) = **line;
		return ;
	}
	if (**line == '\n' || **line == ';')
		*((*str)++) = S_LINE;
	else if (ft_isspace(**line) || **line == '\'' || **line == '"')
		*((*str)++) = S_WORD;
	else if (**line == '<' || **line == '>' || **line == '|')
	{
		if (**line == '|' \
				|| ((*line) != get_cursor()->line->ptr \
					&& !ft_isdigit(*((*line) - 1)))) //TODO: test
			*((*str)++) = S_WORD;
		assign_redirection(str, line);
		*((*str)++) = S_WORD;
	}
	else
		*((*str)++) = **line;
}

static void		to_string_loop(char *str, char *line)
{
	int			count;
	char		skip;

	count = 0;
	skip = FALSE;
	while (line && count < LINE_SIZE)
	{
		if (skip == *line)
		{
			skip = FALSE;
			assign(&str, &line, skip);
		}
		else
		{
			assign(&str, &line, skip);
			if (*line == '\'' || *line == '"')
				skip = *line;
		}
		line++;
		count++;
	}
	*str = 0;
}

char			*to_string(void)
{
	static char	str[LINE_SIZE * 3 + 1];

	ft_bzero(str, LINE_SIZE * 3 + 1);
	to_string_loop(str, (char *)get_cursor()->line->ptr);
	return (str);
}
