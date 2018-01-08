/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 03:22:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/14 11:27:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	btree_assign_child(t_btree *tmp, void *item)
{
	if (!btree_child_left(tmp))
		tmp->left = btree_create_leaf(item);
	else if (!btree_child_right(tmp))
		tmp->right = btree_create_leaf(item);
	return ;
}

int		btree_miss_child(t_btree *tmp)
{
	if (!tmp->left || !tmp->right)
		return (1);
	return (0);
}

void	btree_insert_data(t_btree **root, void *item,
			int (*cmpf)(void *, void*))
{
	t_btree *tmp;

	if (!*root)
	{
		*root = btree_create_leaf(item);
		return ;
	}
	tmp = *root;
	while (1)
	{
		if (btree_miss_child(tmp))
		{
			btree_assign_child(tmp, item);
			return ;
		}
		if (cmpf(item, tmp->left->content) <= 0)
			tmp = btree_child_left(tmp);
		else
			tmp = btree_child_right(tmp);
	}
}
