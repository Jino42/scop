/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 02:11:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 02:22:14 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	btree_apply_infix(t_btree *node, void (*apply)(void *))
{
	if (btree_child_left(node))
		btree_apply_infix(btree_child_left(node), apply);
	apply(node->content);
	if (btree_child_right(node))
		btree_apply_infix(btree_child_right(node), apply);
}
