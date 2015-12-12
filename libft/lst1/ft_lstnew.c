/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 22:07:36 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/03 17:45:49 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne un maillon “frais”. Les champs content
** et content_size du nouveau maillon sont initialisés par copie des
** paramètres de la fonction. Si le paramètre content est nul, le champs
** content est initialisé à NULL et le champs content_size est initialisé à
** 0 que la valeur du paramètre content_size. Le champ next est initialisé
** à NULL. Si l’allocation échoue, la fonction renvoie NULL
*/

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
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
	new->next = NULL;
	return (new);
}
