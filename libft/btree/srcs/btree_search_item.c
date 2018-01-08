/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 04:48:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/14 11:26:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		*btree_search_item(t_btree *root, void *ref,
		int (*cmpf)(void *, void *))
{
	while (1)
	{
		if (!root)
			return (NULL);
		if (!cmpf(ref, root->content))
			return (root);
		if (btree_child_left(root) && cmpf(ref, root->left->content) <= 0)
			root = btree_child_left(root);
		else
			root = btree_child_right(root);
	}
}
