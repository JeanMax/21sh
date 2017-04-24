/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 20:59:31 by mcanal            #+#    #+#             */
/*   Updated: 2017/04/24 19:21:34 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exec the appropriate redirection function
*/

#include "redirection.h"

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
	void	(*const f[])(char **) = {
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
