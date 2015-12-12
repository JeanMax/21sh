/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 17:07:11 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 15:56:41 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Return a line read in a file descriptor.
** The first one parametre is the file descriptor, the second parametre is
** the address of a string which will store the line read on the file
** descriptor. The return value can be 1, 0 or -1 as a line has been read,
** as the reading is done, either that an error happened respectively.
*/

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static size_t	list_len(t_list *link, size_t len)
{
	if (!link)
		return (0);
	if (ft_memchr(link->content, 0, link->content_size))
		return (len + link->content_size);
	return (list_len(link->next, len + link->content_size));
}

static t_list	*cpyfree_list(t_list *link, char *s)
{
	t_list	*next;

	if (!link)
		return (NULL);
	next = link->next;
	ft_memcpy((void *)s, link->content, link->content_size);
	s += link->content_size;
	if (ft_memchr(link->content, 0, link->content_size))
	{
		ft_lstfree(&link);
		return (next);
	}
	ft_lstfree(&link);
	return (cpyfree_list(next, s));
}

static int		fill_line(t_list **fst_link, char **line)
{
	if (!(*line = (char *)malloc(sizeof(char) * list_len(*fst_link, 0))))
		return (-1);
	*fst_link = cpyfree_list(*fst_link, *line);
	return (1);
}

static void		add_links(t_list **fst_link, char *s, size_t len)
{
	char	*eol;
	size_t	line_len;

	if (!(eol = ft_memchr(s, '\n', len)))
	{
		ft_lstaddlast(fst_link, ft_lstnew(s, len));
		return ;
	}
	line_len = (size_t)(eol - s) + 1;
	*eol = 0;
	ft_lstaddlast(fst_link, ft_lstnew(s, line_len));
	if (line_len != len)
		add_links(fst_link, s + line_len, len - line_len);
}

int				get_next_line(int const fd, char **line)
{
	ssize_t			ret;
	char			buf[BUFF_SIZE];
	static t_list	*fst_link = NULL;

	if (fd < 0 || !line)
		return (-1);
	if (fst_link && ft_memchr(fst_link->content, 0, fst_link->content_size))
		return (fill_line(&fst_link, line));
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		add_links(&fst_link, buf, (size_t)ret);
		if (ft_memchr(buf, 0, (size_t)ret))
			return (fill_line(&fst_link, line));
	}
	return ((int)ret);
}
