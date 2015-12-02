/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 17:28:37 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 01:33:59 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Parcourt la liste lst en appliquant à chaque maillon la fonction f
** et crée une nouvelle liste “fraiche” avec malloc(3) résultant des
** applications successives. Si une allocation échoue, la fonction renvoie NULL.
*/

#include "libft.h"

t_lst			*ft_lmap(t_lst *alst, t_lst *(*f)(t_lst *elem))
{
	t_lst	*new_alst;
	t_lst	*new_list;
	t_lst	*tmp;

	if (!alst || !f)
		return (NULL);
	tmp = f(alst);
	if (!(new_list = ft_lnew(tmp->content, tmp->content_size)))
		return (NULL);
	new_alst = new_list;
	while (alst->next)
	{
		tmp = f(alst->next);
		if (!(new_list->next = ft_lnew(tmp->content, tmp->content_size)))
			return (NULL);
		new_list->next->prev = new_list;
		new_list = new_list->next;
		alst = alst->next;
	}
	return (new_alst);
}
