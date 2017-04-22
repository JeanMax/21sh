/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:33:07 by mcanal            #+#    #+#             */
/*   Updated: 2016/05/21 16:40:58 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free the whole tree
*/

#include "libft.h"

void	ft_bstdel(t_bst **root, t_del *del)
{
	if (!*root)
		return ;
	ft_bstdel(&(*root)->left, del);
	ft_bstdel(&(*root)->right, del);
	del((*root)->content, (*root)->content_size);
	ft_memdel((void *)root);
}
