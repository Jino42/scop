/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 18:52:20 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/14 11:27:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_btree	*btree_create_node(void *content, t_btree *btree_left,
		t_btree *btree_right)
{
	t_btree *ptr;

	ptr = NULL;
	if (!(ptr = ft_memalloc(sizeof(t_btree))))
		return (NULL);
	ptr->left = btree_left;
	ptr->right = btree_right;
	ptr->content = content;
	return (ptr);
}
