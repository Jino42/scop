/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 10:12:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/19 15:42:37 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	btree_apply_free(t_btree *node, void (*apply)(void *))
{
	if (!node)
		return ;
	apply(node->content);
	if (btree_child_left(node))
		btree_apply_free(btree_child_left(node), apply);
	if (btree_child_right(node))
		btree_apply_free(btree_child_right(node), apply);
	free(node);
}
