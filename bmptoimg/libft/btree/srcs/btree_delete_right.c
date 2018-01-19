/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_delete_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:05:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/10 00:13:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		*btree_delete_right(t_btree *node)
{
	void *ptr;

	if (node && btree_is_leaf(node->right))
	{
		ptr = node->right->content;
		ft_memdel((void*)&node->right);
		return (ptr);
	}
	return (NULL);
}
