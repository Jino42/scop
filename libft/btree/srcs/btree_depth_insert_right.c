/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_depth_insert_right.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:52:34 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 00:58:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	btree_depth_insert_right(t_btree *node, void *item)
{
	t_btree *tmp;

	if (!node)
		btree_create_leaf(item);
	else
	{
		tmp = node;
		while (btree_child_right(tmp))
			tmp = btree_child_right(tmp);
		tmp->right = btree_create_leaf(item);
	}
}
