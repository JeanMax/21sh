/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/15 01:19:36 by mcanal           ###   ########.fr       */
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

void			redirect(char **c, t_env *e, int i)
{
	char		free;

	free = need_space(c) ? 1 : 0;
	c = check_cmd(c);
	while (c[++i])
		if (ft_strchr(c[i], '>'))
		{
			(!ft_strcmp(c[i], ">>&")) ? error_d_right(c, e) : (void)0;
			(!ft_strcmp(c[i], ">&")) ? error_s_right(c, e) : (void)0;
			(!ft_strcmp(c[i], ">>")) ? doble_right(c, e) : simple_right(c, e);
			break ;
		}
		else if (ft_strchr(c[i], '<'))
		{
			ft_strstr(c[i], "<<") ? doble_left(c, e) : simple_left(c, e);
			break ;
		}
		else if (ft_strchr(c[i], '|'))
		{
			ft_strstr(c[i], "|&") ? error_pipe(c, e) : simple_pipe(c, e);
			break ;
		}
	free ? ft_freestab(c) : (void)0;
}
