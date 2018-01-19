/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_depth_insert_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:58:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 00:58:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	btree_depth_insert_left(t_btree *node, void *item)
{
	t_btree *tmp;

	if (!node)
		btree_create_leaf(item);
	else
	{
		tmp = node;
		while (btree_child_left(tmp))
			tmp = btree_child_left(tmp);
		tmp->left = btree_create_leaf(item);
	}
}
