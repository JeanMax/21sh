/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 02:31:48 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:21:14 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Parcourt la liste lst en appliquant à chaque maillon la fonction f
** et crée une nouvelle liste “fraiche” avec malloc(3) résultant des
** applications successives. Si une allocation échoue, la fonction renvoie NULL.
*/

#include "libft.h"

t_list			*ft_lstmap(t_list *alst, t_list *(*f)(t_list *elem))
{
	t_list	*new_alst;
	t_list	*new_list;
	t_list	*tmp;

	if (!alst || !f)
		return (NULL);
	tmp = f(alst);
	if (!(new_list = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	new_alst = new_list;
	while (alst->next != NULL)
	{
		tmp = f(alst->next);
		if (!(new_list->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		new_list = new_list->next;
		alst = alst->next;
	}
	return (new_alst);
}
