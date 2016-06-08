/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/08 14:17:07 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exec the appropriate redirection function
*/

#include "redirection.h"

/* debug */
void			debug_arr(char **cmd)
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
		/* ft_putchar_clr('|', "red"); */
		ft_putchar('|');
		cmd++;
	}
	ft_putchar('\n');
}
/* debug */

/*
** get fd from a string
** will try atoi and check if fd valid
*/
int				get_fd(char *s)//, int open_flag)
{
	int		fd;

	if (!s)
		return (-1);
	while (*s && !ft_isdigit(*s) && *s != '-')
		s++;
	if (!*s)
		return (-1);
	fd = ft_atoi(s);
	return (fcntl(fd, F_GETFD) ? -1 : fd);
}

 //TODO:rename
void			do_redirect(char **cmd, enum e_replacement c, int o_flag, \
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

int				is_redirection(char *s)
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

static int		got_pipe_after_dup(char **cmd)
{
	t_bool	got_dup;

	got_dup = FALSE;
	while (*cmd)
	{
		if (ft_strchr(*cmd, R_PIPELINE))
		{
			if (got_dup)
				return (TRUE);
		}
		else if ((ft_strchr(*cmd, R_DUP_INPUT) \
				|| ft_strchr(*cmd, R_DUP_OUTPUT)))
			got_dup = TRUE;
		else if (is_redirection(*cmd))
			return (FALSE);
		cmd++;
	}
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
	if (got_pipe_after_dup(cmd))
		return (R_PIPELINE);
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
	void	(* const f[])(char **) = {
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
