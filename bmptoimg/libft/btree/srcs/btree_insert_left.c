/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_left.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 23:59:23 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 00:21:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		btree_insert_left(t_btree *node, void *item)
{
	if (node && !btree_child_left(node))
		node->left = btree_create_leaf(item);
}
