/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_delete_left.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:14:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 00:14:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		*btree_delete_left(t_btree *node)
{
	void *ptr;

	if (node && btree_is_leaf(node->left))
	{
		ptr = node->left->content;
		ft_memdel((void*)&node->left);
		return (ptr);
	}
	return (NULL);
}
