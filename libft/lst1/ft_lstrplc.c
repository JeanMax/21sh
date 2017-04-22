/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 05:03:09 by mcanal            #+#    #+#             */
/*   Updated: 2014/11/12 23:06:31 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** replace the link 'old' with 'new'
** 'old' won't be deleted, but removed of the list
*/

#include "libft.h"

void	ft_lstrplc(t_list **alst, t_list *old, t_list *new)
{
	t_list *tmp;

	if (!alst || !old || !new)
		return ;
	tmp = *alst;
	if (tmp != old)
	{
		while (tmp->next != old && tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->next = old->next;
	old->next = NULL;
}
