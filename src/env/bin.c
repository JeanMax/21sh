/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 00:00:33 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/22 13:09:46 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

static int		cmp(const void *a, const void *b)
{
	char	*s1;
	char	*s2;

	if (!(s1 = ft_strrchr((char *)((t_bst *)a)->content, '/')))
		s1 = (char *)((t_bst *)b)->content;
	else
		s1++;
	if (!(s2 = ft_strrchr((char *)((t_bst *)b)->content, '/')))
		s2 = (char *)((t_bst *)b)->content;
	else
		s2++;
	return (ft_strcmp(s1, s2));
}

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
		while ((s_dir = readdir(dir)))
		{
			tmp = ft_strjoin(*path, "/");
			f_name = ft_strjoin(tmp, s_dir->d_name);
			if ((!stat(f_name, &s_stat) && S_ISREG(s_stat.st_mode)) \
				&& (s_stat.st_mode & S_IXUSR))
				ft_bstavladd(&e->bin_root, f_name, ft_strlen(f_name) + 1, cmp);
			ft_memdel((void *)&f_name);
			ft_memdel((void *)&tmp);
		}
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
		if (e->bin_root)
			ft_bstclean(&e->bin_root);
		check_dir(path_arr, e);
	}
	ft_arrdel(&path_arr);
}

char			*get_full_bin(char *bin)
{
	t_bst	*found;

	if ((found = *(ft_bstsearch(\
					&get_env_struct()->bin_root, bin, ft_strlen(bin), cmp))))
		return ((char *)found->content);
	return (NULL);
}
