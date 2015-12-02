/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdellink.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 23:55:52 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:23:05 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** retire un élément 'n' de la liste, mais ne le supprime pas!
** l'élément 'n-1' pointera sur l'élément 'n+1'
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
