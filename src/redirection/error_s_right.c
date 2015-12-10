/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_s_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 23:21:07 by mcanal            #+#    #+#             */
/*   Updated: 2015/02/12 19:50:04 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stderr redirection handler (>&)
** this is also redirecting stdout
*/

#include "flex_shell.h"

static void	check_error(char **cmd, char *pgm)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (ft_strcmp(">&", cmd[i - 1]) && ft_strcmp(">&", cmd[i]))
		{
			ft_putstr_fd(pgm, 2);
			if (!ft_strcmp("ls", pgm))
			{
				ft_putstr_fd(": cannot access ", 2);
			}
			else
				ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd(": No such file or directory ", 2);
		}
		i++;
	}
}

static char	**check_cmd(char **cmd)
{
	int		i;
	int		j;
	int		ac;

	ac = 0;
	while (cmd[ac])
		ac++;
	i = 0;
	while (cmd[i] && ft_strcmp(">&", cmd[i]))
		i++;
	check_error(&cmd[i], cmd[0]);
	j = ac - 1;
	while (cmd[j] && ft_strcmp(">&", cmd[j]))
		j--;
	if (i == j)
		return (cmd);
	cmd[i + 1] = cmd[j + 1];
	i += 2;
	while (cmd[i])
	{
		cmd[i] = NULL;
		i++;
	}
	return (cmd);
}

static int	is_ambiguous(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], ">&"))
		i++;
	if (!cmd[i])
		return (0);
	i++;
	while (cmd[i] && !ft_strchr(cmd[i], '>') && !ft_strchr(cmd[i], '<')\
			&& !ft_strchr(cmd[i], '|'))
		i++;
	if (cmd[i])
		return (1);
	return (0);
}

static void	handle_fd(int file_fd, char **cmd, t_env *e)
{
	int		err_fd;
	int		in_fd;

	in_fd = dup(1);
	err_fd = dup(2);
	dup2(file_fd, 1);
	dup2(file_fd, 2);
	launch_cmd(cmd, e);
	dup2(in_fd, 1);
	dup2(err_fd, 2);
	close(file_fd);
	close(err_fd);
	close(in_fd);
}

void		error_s_right(char **cmd, t_env *e)
{
	int		file_fd;
	int		i;

	cmd = is_ambiguous(cmd) ? cmd : check_cmd(cmd);
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], ">&"))
		i++;
	!cmd[i + 1] ? failn("Missing name for redirect.") : 0;
	!ft_strcmp(cmd[0], ">&") && cmd[i + 1] ? failn("Invalid null command.") : 0;
	is_ambiguous(cmd) && ft_strcmp(cmd[0], ">&") && cmd[i + 1] ?\
		failn("Ambiguous output redirect.") : 0;
	if (!cmd[i + 1] || !ft_strcmp(cmd[0], ">&") || is_ambiguous(cmd))
		return ;
	if ((file_fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
		error("open", cmd[i + 1]);
	while (cmd[i])
		ft_memdel((void *)&cmd[i++]);
	handle_fd(file_fd, cmd, e);
}
