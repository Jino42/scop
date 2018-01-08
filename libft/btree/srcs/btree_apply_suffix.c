/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 02:12:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 02:22:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	btree_apply_suffix(t_btree *node, void (*apply)(void *))
{
	if (btree_child_left(node))
		btree_apply_suffix(btree_child_left(node), apply);
	if (btree_child_right(node))
		btree_apply_suffix(btree_child_right(node), apply);
	apply(node->content);
}
