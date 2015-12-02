/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 22:22:30 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 20:53:45 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free the whole list
*/

#include "libft.h"

void	ft_lstclean(t_list **alst)
{
	t_list	*next;

	if (!*alst)
		return ;
	next = (*alst)->next;
	ft_lstfree(alst);
	ft_lstclean(&next);
}
