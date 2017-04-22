/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 05:25:28 by mcanal            #+#    #+#             */
/*   Updated: 2016/03/12 19:22:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return the address of the first link where content == data
*/

#include "libft.h"

t_list			**ft_lstfind(t_list **alst, void *data, t_cmp *cmp)
{
	if (!(*alst) || !cmp(*alst, data))
		return (alst);
	return (ft_lstfind(&(*alst)->next, data, cmp));
}
