/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 02:29:26 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/28 18:35:50 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** apply the function f to each link of the list
*/

#include "libft.h"

void			ft_liter(t_lst *alst, void (*f)(t_lst *elem))
{
	if (!alst)
		return ;
	f(alst);
	ft_liter(alst->next, f);
}
