/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstavldel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 22:23:30 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/12 00:16:52 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** remove and free a node
*/

#include "libft.h"

static int		h(t_bst *node)
{
	return (node ? (int)node->height : 0);
}

static t_bst	*rot_right(t_bst *root, int ret)
{
	t_bst	*node;

	if (ret > 0)
	{
		node = root->right->left;
		root->right->left = node->right;
		node->right = root->right;
		root->right = node;
		node->height = (size_t)ft_max(h(node->left), h(node->right)) + 1;
		root->right->height = (size_t)\
			ft_max(h(root->right->left), h(root->right->right)) + 1;
	}
	node = root->right;
	root->right = node->left;
	node->left = root;
	node->height = (size_t)ft_max(h(node->left), h(node->right)) + 1;
	root->height = (size_t)ft_max(h(root->left), h(root->right)) + 1;
	return (node);
}

static t_bst	*rot_left(t_bst *root, int ret)
{
	t_bst	*node;

	if (ret < 0)
	{
		node = root->left->right;
		root->left->right = node->left;
		node->left = root->left;
		root->left = node;
		node->height = (size_t)ft_max(h(node->left), h(node->right)) + 1;
		root->left->height = (size_t)\
			ft_max(h(root->left->left), h(root->left->right)) + 1;
	}
	node = root->left;
	root->left = node->right;
	node->right = root;
	node->height = (size_t)ft_max(h(node->left), h(node->right)) + 1;
	root->height = (size_t)ft_max(h(root->left), h(root->right)) + 1;
	return (node);
}

static t_bst	*del_loop(t_bst *node, t_bst *to_del, \
							int (*cmp)(const void *a, const void *b))
{
	int	ret;

	if (!node)
		return (NULL);
	if ((ret = cmp(node, to_del)) < 0)
		node->left = del_loop(node->left, to_del, cmp);
	else if (ret > 0)
		node->right = del_loop(node->right, to_del, cmp);
	else
		ft_bstdel(&node);
	if (!node)
		return (NULL);
	node->height = (size_t)ft_max(h(node->left), h(node->right)) + 1;
	if ((ret = h(node->left) - h(node->right)) > 1)
		node = rot_left(node, node->right ? \
							h(node->right->left) - h(node->right->right) : 0);
	else if (ret < -1)
		node = rot_right(node, node->left ?\
							h(node->left->left) - h(node->left->right) : 0);
	return (node);
}

void			ft_bstavldel(t_bst **root, t_bst **to_del,
							int (*cmp)(const void *a, const void *b))
{
	*root = del_loop(*root, *to_del, cmp);
}
