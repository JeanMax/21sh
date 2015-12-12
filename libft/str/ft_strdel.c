/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:41:06 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/05 21:51:06 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Takes in parameter the address of a character string which
** must be freed with free (3) and his pointer set to NULL.
*/

#include "libft.h"

void	ft_strdel(char **as)
{
	ft_memdel((void *)as);
}
