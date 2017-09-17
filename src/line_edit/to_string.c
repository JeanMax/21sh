/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:58:45 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/17 18:08:26 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TODO: rewrite that shit
*/

#include "line_edit.h"

static void		assign_redirection(t_arr *str, char **line)
{
	if (**line == '>')
	{
		if (*((*line) + 1) == '>' && *++(*line))
			ft_arrpush(str, (void *)(long)R_OUTPUT_APPEND, -1);
		else if (*((*line) + 1) == '&' && *++(*line))
			ft_arrpush(str, (void *)(long)R_DUP_OUTPUT, -1);
		else
			ft_arrpush(str, (void *)(long)R_OUTPUT, -1);
	}
	else if (**line == '<')
	{
		if (*((*line) + 1) == '<' && *++(*line))
			ft_arrpush(str, (void *)(long)R_HERE_DOC, -1);
		else if (*((*line) + 1) == '&' && *++(*line))
			ft_arrpush(str, (void *)(long)R_DUP_INPUT, -1);
		else
			ft_arrpush(str, (void *)(long)R_INPUT, -1);
	}
	else
		ft_arrpush(str, (void *)(long)R_PIPELINE, -1);
}

static void		assign_env(t_arr *str, char **line)
{
	char *swap;
	char *env_var;
	char save;

	swap = ++(*line);
	while (*swap && (ft_isalnum(*swap) || *swap == '_'))
		swap++;
	save = *swap;
	*swap = 0;
	if ((env_var = get_env(*line)))
	{
		env_var += (size_t)(swap - *line) + 1;
		while (*env_var)
			ft_arrpush(str, (void *)(long)*env_var++, -1);
	}
	*swap = save;
	*line = swap - 1;
}

static void		assign(t_arr *str, char **line, char skip)
{
	if (**line == '$' && skip != '\'')
		assign_env(str, line);
	else if (skip)
		ft_arrpush(str, (void *)(long)**line, -1);
	else if (**line == '\n' || **line == ';')
		ft_arrpush(str, (void *)(long)S_LINE, -1);
	else if (ft_isspace(**line))
		ft_arrpush(str, (void *)(long)S_WORD, -1);
	else if (**line == '<' || **line == '>' || **line == '|')
	{
		if (**line == '|' \
				|| ((*line) != get_cursor()->line->ptr \
					&& !ft_isdigit(*((*line) - 1))))
			ft_arrpush(str, (void *)(long)S_WORD, -1);
		assign_redirection(str, line);
		ft_arrpush(str, (void *)(long)S_WORD, -1);
	}
	else if (**line != '\'' && **line != '"')
		ft_arrpush(str, (void *)(long)**line, -1);
}

static void		to_string_loop(t_arr *str, char *line)
{
	char		skip;

	skip = FALSE;
	while (line && *line)
	{
		if (skip == *line)
		{
			skip = FALSE;
			assign(str, &line, skip);
		}
		else
		{
			assign(str, &line, skip);
			if (!skip && (*line == '\'' || *line == '"'))
				skip = *line;
		}
		line++;
	}
	ft_arrpush(str, (void *)(long)0, -1);
}

char			*to_string(void)
{
	static t_arr	*str = NULL;

	if (!str)
		str = ft_arrnew(LINE_SIZE, sizeof(char));
	else
		str->length = 0;
	to_string_loop(str, (char *)get_cursor()->line->ptr);
	return ((char *)str->ptr);
}
