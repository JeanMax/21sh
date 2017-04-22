/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 04:58:45 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/12 19:21:57 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the address of the first link where content == data
*/

#include "libft.h"

t_lst	**ft_lfind(t_lst **alst, void *data, t_cmp *cmp)
{
	if (!(*alst) || !cmp(*alst, data))
		return (alst);
	return (ft_lfind(&(*alst)->next, data, cmp));
}
