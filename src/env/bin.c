/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 00:00:33 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/14 13:16:12 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

static void		check_dir(char **path, t_env *e)
{
	DIR				*dir;
	struct dirent	*s_dir;
	struct stat		s_stat;
	char			*f_name;
	char			*tmp;

	if (!path || !*path)
		return ;
	if ((dir = opendir(*path)))
	{
		if (!stat(*path, &s_stat) && s_stat.st_mtime > e->last_update)
			e->last_update = s_stat.st_mtime;
		tmp = ft_strjoin(*path, "/");
		while ((s_dir = readdir(dir)))
		{
			f_name = ft_strjoin(tmp, s_dir->d_name);
			if ((!stat(f_name, &s_stat) && S_ISREG(s_stat.st_mode)) \
				&& (s_stat.st_mode & S_IXUSR) \
				&& !ft_hget(e->bin_table, s_dir->d_name))
				ft_hset(e->bin_table, ft_strdup(s_dir->d_name), f_name);
			else
				ft_memdel((void *)&f_name);
		}
		ft_memdel((void *)&tmp);
		closedir(dir);
	}
	check_dir(path + 1, e);
}

static t_bool	is_up_to_date(char **path, time_t last_update)
{
	DIR				*dir;
	struct stat		s_stat;
	t_bool			ret;

	if (!path || !*path)
		return (TRUE);
	ret = TRUE;
	if ((dir = opendir(*path)))
	{
		if (!stat(*path, &s_stat) && s_stat.st_mtime > last_update)
			ret = FALSE;
		closedir(dir);
	}
	return (ret && is_up_to_date(path + 1, last_update));
}

void			update_bin(t_bool force_update)
{
	char	**path_arr;
	char	*path;
	t_env	*e;

	e = get_env_struct();
	path_arr = NULL;
	if ((path = get_env("PATH")))
		path_arr = ft_strsplit(path + 5, ':');
	if (force_update || !is_up_to_date(path_arr, e->last_update))
	{
		init_table(&e->bin_table);
		check_dir(path_arr, e);
	}
	ft_arr_del(&path_arr);
}

char			*get_full_bin(char *bin)
{
	return (ft_hget(get_env_struct()->bin_table, bin));
}
