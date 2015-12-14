/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/13 22:27:37 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** launch the appropriate redirection function
*/

#include "flex_shell.h"

static int		need_space(char **cmd)
{
	char		*s;

	while (*cmd)
	{
		s = *cmd;
		while (*(s + 1))
		{
			if (((*s == '>' || *s == '<' || *s == '|' || *s == '&')\
				&& (*(s + 1) != '>' && *(s + 1) != '<' && *(s + 1) != '|' \
			&& *(s + 1) != '&')) || ((*s != '>' && *s != '<' && *s != '|'\
			&& *s != '&') && (*(s + 1) == '>' || *(s + 1) == '<'\
			|| *(s + 1) == '|' || *(s + 1) == '&')))
				return (1);
			s++;
		}
		cmd++;
	}
	return (0);
}

static char		**check_cmd(char **c)
{
	if (!need_space(c))
		return (c);
	return (spaces_error(c));
}

void			redirect(char **c, int i)
{
	char		free;

	free = need_space(c) ? 1 : 0;
	c = check_cmd(c);
	while (c[++i])
		if (ft_strchr(c[i], '>'))
		{
			(!ft_strcmp(c[i], ">>&")) ? error_d_right(c) : (void)0;
			(!ft_strcmp(c[i], ">&")) ? error_s_right(c) : (void)0;
			(!ft_strcmp(c[i], ">>")) ? doble_right(c) : simple_right(c);
			break ;
		}
		else if (ft_strchr(c[i], '<'))
		{
			ft_strstr(c[i], "<<") ? doble_left(c) : simple_left(c);
			break ;
		}
		else if (ft_strchr(c[i], '|'))
		{
			ft_strstr(c[i], "|&") ? error_pipe(c) : simple_pipe(c);
			break ;
		}
	free ? ft_arrdel(&c) : (void)0;
}
