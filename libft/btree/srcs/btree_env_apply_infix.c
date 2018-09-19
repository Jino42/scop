/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_env_apply_infix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 02:11:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 21:36:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	btree_env_apply_infix(void *env, t_btree *node,
											void (*apply)(void *, void *))
{
	if (btree_child_left(node))
		btree_env_apply_infix(env, btree_child_left(node), apply);
	apply(env, node->content);
	if (btree_child_right(node))
		btree_env_apply_infix(env, btree_child_right(node), apply);
}
