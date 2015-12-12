/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:23:57 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/11 17:06:18 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne un maillon “frais”. Les champs content
** et content_size du nouveau maillon sont initialisés par copie des paramètre
** de la fonction. Si le paramètre content est nul, le champs content es
** initialisé à NULL et le champs content_size est initialisé à 0 que
** la valeur du paramètre content_size. Les champs left/right sont initialisés
** à NULL.
** Si l’allocation échoue, la fonction renvoie NULL
*/

#include "libft.h"
#include <stdlib.h>

t_bst	*ft_bstnew(void *content, size_t content_size)
{
	t_bst	*new;

	if (!(new = malloc(sizeof(t_bst))))
		return (NULL);
	if (content)
	{
		if (!(new->content = malloc(content_size)))
			return (NULL);
		new->content_size = content_size;
		ft_memcpy(new->content, content, content_size);
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->left = NULL;
	new->right = NULL;
	new->height = 1;
	return (new);
}
