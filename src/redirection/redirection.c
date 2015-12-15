/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/15 07:28:57 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exec the appropriate redirection function
*/

#include "redirection.h"

/*
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
*/

/* debug */
void	debug_arr(char **cmd)
{
	char	*s;

	while (*cmd)
	{
		s = *cmd;
		while (*s)
		{
			if (*s == S_WORD)
				ft_putstr("' '");
			else if (*s == S_LINE)
				ft_putstr("';'");
			else if (*s == R_OUTPUT)
				ft_putstr("'>'");
			else if (*s == R_OUTPUT_APPEND)
				ft_putstr("'>>'");
			else if (*s == R_INPUT)
				ft_putstr("'<'");
			else if (*s == R_PIPELINE)
				ft_putstr("'|'");
			else if (*s == R_HERE_DOC)
				ft_putstr("'<<'");
			else if (*s == R_DUP_INPUT)
				ft_putstr("'<&'");
			else if (*s == R_DUP_OUTPUT)
				ft_putstr("'>&'");
			else
				ft_putchar(*s);
			s++;
		}
		ft_putchar_clr('|', "red");
		cmd++;
	}
	ft_putchar('\n');
}
/* debug */

/*
** get fd from a string
** will try atoi and check if fd valid, otherwise will open s as a filename
*/
static int		get_fd(char *s)//, int open_flag)
{
	int		fd;

	if (!s)
		return (-1);
	while (*s && (!ft_isdigit(*s) || *s != '-'))
		s++;
	if (!*s)
		return (-1);
	fd = ft_atoi(s);
	return (fcntl(fd, F_GETFD) ? -1 : fd);
/*
	if (!open_flag)
	return (-1);
	return (open(s, open_flag, 0664));
*/
}

 //TODO:rename
void		do_redirect(char **cmd, enum e_replacement c, int o_flag,	\
						void (*do_stuff_with_cmd_and_fd_now)(char **, int, int))
{
	int		fd_left;
	int		fd_right;
	char	**swap;
	char	*tmp;

	swap = cmd;
	while (*(++swap) && !(tmp = ft_strchr(*swap, c)))
		;
	if (*swap == tmp || (fd_left = get_fd(*swap)) == -1)
	{
		fd_left = c == R_INPUT ? STDIN_FILENO : STDOUT_FILENO;
		*tmp = 0;
	}
	if ((fd_right = open(*(++swap), o_flag, 0664)) == -1)
		error(E_OPEN | E_NOEXIT, *swap); //TODO
	if (*tmp || tmp == *(swap - 1))
	{
		tmp = *swap;
		ft_arrdelone(cmd, *(swap - 1));
		ft_arrdelone(cmd, tmp);
	}
	else
		ft_arrdelone(cmd, *swap);
	do_stuff_with_cmd_and_fd_now(cmd, fd_left, fd_right);
}

static int		is_redirection(char *s)
{
	char	*ret;

	if (s && ((ret = ft_strchr(s, R_OUTPUT)) || \
				(ret = ft_strchr(s, R_OUTPUT_APPEND)) || \
				(ret = ft_strchr(s, R_DUP_OUTPUT)) || \
				(ret = ft_strchr(s, R_INPUT)) || \
				(ret = ft_strchr(s, R_HERE_DOC)) || \
				(ret = ft_strchr(s, R_DUP_INPUT)) || \
				(ret = ft_strchr(s, R_PIPELINE))))
		return (*ret);
	return (FALSE);
}

static int		got_redirection(char **cmd)
{
	int	ret;

	if (is_redirection(*cmd))
	{
		failn("21sh: Invalid null command.");
		return (-1);
	}
	while (*(++cmd))
		if ((ret = is_redirection(*cmd)))
		{
			if (!*(cmd + 1))
			{
				failn("21sh: Missing name for redirect.");
				return (-1);
			}
			else if (is_redirection(*(cmd + 1)))
			{
				failn("21sh: Syntax error.");
				return (-1);
			}
			return (ret);
		}
	return (FALSE);
}

/*
** exec the appropriate redirection (may call exec_cmd recursivly)
** return true if the exec process is handled,
** return false if the cmd does not include a redirection. exec still needed
*/
t_bool			exec_redirection(char **cmd)
{
	int		redirection_index;
	void	(*f[])(char **) =
		{
			output_redirect,
			output_append_redirect,
			input_redirect,
			pipeline,
			here_doc,
			dup_input,
			dup_output
		};

	if ((redirection_index = got_redirection(cmd)))
	{
		if (redirection_index != -1)
			f[redirection_index - R_OUTPUT](cmd);
		return (TRUE);
	}
	return (FALSE);
}
