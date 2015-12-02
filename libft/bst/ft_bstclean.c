/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstclean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:33:07 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 20:52:12 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free the whole tree
*/

#include "libft.h"

void	ft_bstclean(t_bst **root)
{
	if (!*root)
		return ;
	ft_bstclean(&(*root)->left);
	ft_bstclean(&(*root)->right);
	ft_bstfree(root);
}
