/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 01:56:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 02:16:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	btree_apply_prefix(t_btree *node, void (*apply)(void *))
{
	apply(node->content);
	if (btree_child_left(node))
		btree_apply_prefix(btree_child_left(node), apply);
	if (btree_child_right(node))
		btree_apply_prefix(btree_child_right(node), apply);
}
