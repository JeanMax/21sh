/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstavladd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 01:57:44 by mcanal            #+#    #+#             */
/*   Updated: 2015/11/29 14:11:12 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** balance a tree using left/right rotations (AVL)
*/

#include "libft.h"

static void	ft_bstbalance(t_bst **root)
{
	int	balance;

	if ((balance = ft_bstgetbalance(*root)) > 1)
	{
		
	}
	else if (balance < -1)
	{
		
	}
}

t_bst		*ft_bstavladd(t_bst **root, void *content, size_t content_size, \
						 int (*cmp)(const void *a, const void *b, size_t n))

{
	int	ret;

	if (!*root)
		return (*root = ft_bstnew(content, content_size));
	
	if (!(ret = cmp(content, root->content, 
				(size_t)ft_min((int)root->content_size, (int)content_size))))
		return (NULL);
	else if (ret < 0)
		root->left = ft_bstavladd();
	else

}
