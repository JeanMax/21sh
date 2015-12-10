/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 18:44:22 by mcanal            #+#    #+#             */
/*   Updated: 2015/09/15 01:20:53 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** handle spaces error in cmd tabs :
** "X>", "Y" wille be corrected in "X", ">", "Y"
** same idea for ">Y" and "X>Y"
** also working for any other str than ">" (basically ">>", ">", "|", "<", "<<")
*/

#include "flex_shell.h"

static int		tab_len(char **c, int len, char *s)
{
	while (*c)
	{
		s = *c;
		if ((ft_strchr(s, '>') || ft_strchr(s, '<') || ft_strchr(s, '|')))
		{
			len += (!ft_strcmp(s, "<<") || !ft_strcmp(s, ">>") ||\
					!ft_strcmp(s, "|&") || !ft_strcmp(s, ">&") || !ft_strcmp(s, ">>&")) ? 1 : 0;
			len += (*s != '>' && *s != '<' && *s != '|' && *s != '&') ? 1 : 0;
			s += ((*(s + 1) == '>' || *(s + 1) == '&') && *s == '>') ||\
				(*(s + 1) == '<' && *s == '<') || (*(s + 1) == '&' && *s == '|') ? 1 : 0;
			while (*s)
			{
				if (*s == '>' || *s == '<' || *s == '|' || *s == '&')
					len += *(s + 1) ? 2 : 1;
				s += ((*(s + 1) == *s || *(s + 1) == '&') && *s == '>') || \
					(*(s + 1) == *s && *s == '<') || (*(s + 1) == '&' && *s == '|') ? 2 : 1;
			}
			len -= (((*(s - 1) == *(s - 2) || ((*(s - 2) == '>' ||\
												*(s - 2) == '|') && *(s - 1) == '&')) && (*(s - 2) == '>' ||\
																							*(s - 2) == '<' || *(s - 2) == '|'))) ? 2 : 1;
		}
		len += !ft_strcmp(s - 3, ">>&") ? 0 : 1;
		c++;
	}
	return (len);
}

static size_t	count_it(char *s1)
{
	size_t	i;

	i = 0;
	if (*s1 != '>' && *s1 != '<' && *s1 != '|' && *s1 != '&')
		while (*s1 && *s1 != '>' && *s1 != '<' && *s1 != '|' && *s1 != '&')
		{
			i++;
			s1++;
		}
	else
	{
		while (*s1 && (*s1 == '>' || *s1 == '<' || *s1 == '|' || *s1 == '&'))
		{
			i++;
			s1++;
		}
	}
	return (i);
}

static void		add_spaces(char **c1, char **c2)
{
	size_t	i;
	char	*s;

	while (*c1)
	{
		s = *c1;
		while (*s)
		{
			i = count_it(s);
			*c2 = ft_strndup(s, i);
			c2++;
			s += i;
		}
		c1++;
	}
}

char			**spaces_error(char **cmd1)
{
	char	**cmd2;
	int		i;

	i = tab_len(cmd1, 0, 0);
	cmd2 = (char **)malloc(sizeof(char *) * (size_t)(i + 1));
	cmd2[i] = NULL;
	add_spaces(cmd1, cmd2);
	return (cmd2);
}
