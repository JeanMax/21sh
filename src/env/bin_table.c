/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 13:14:05 by mc                #+#    #+#             */
/*   Updated: 2017/09/14 13:18:24 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

static size_t	hash(const void *content, size_t content_size)
{
	(void)content_size;
	return (ft_jenkins_hash((char *)content, ft_strlen((char *)content)));
}

static int		cmp(const void *a, const void *b, size_t n)
{
	(void)n;
	return (ft_strcmp(*(char **)a, *(char **)b));
}

static void		del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void			init_table(t_htable **table)
{
	size_t prev_size;

	prev_size = 0;
	if (*table)
	{
		prev_size = (*table)->bucket_size;
		ft_hdel(table);
	}
	*table = ft_hnew(prev_size);
	(*table)->hash = hash;
	(*table)->key_cmp = cmp;
	(*table)->value_cmp = cmp;
	(*table)->key_del = del;
	(*table)->value_del = del;
}
