/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 23:56:08 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/09 23:59:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		btree_insert_right(t_btree *node, void *item)
{
	if (node && !btree_child_right(node))
		node->right = btree_create_leaf(item);
}
