/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 04:37:18 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 20:55:37 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free a link
*/

#include "libft.h"

void	ft_lfree(t_lst **link)
{
	ft_memdel((void *)&(*link)->content);
	ft_memdel((void *)link);
}
