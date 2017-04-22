/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdellink.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 23:55:52 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/21 16:47:59 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** remove a link 'n' from the list, but does not delete it!
** the element n-1 will be linked with the element n+1
*/

#include "libft.h"

void	ft_lstdellink(t_list **alst, t_list *link)
{
	t_list	*tmp;

	if (!*alst || !link)
		return ;
	tmp = *alst;
	while (tmp->next != NULL && tmp->next != link)
		tmp = tmp->next;
	if (tmp->next == NULL)
		return ;
	tmp->next = link->next;
	link->next = NULL;
}
