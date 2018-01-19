/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_infix_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:01:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/14 11:26:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		btree_insert_infix_data(t_btree **root, void *item,
		int (*cmpf)(void *, void *))
{
	if (!*root)
	{
		*root = btree_create_leaf(item);
		return ;
	}
	if (cmpf(item, (*root)->content) <= 0)
		btree_insert_infix_data(&(*root)->left, item, cmpf);
	else
		btree_insert_infix_data(&(*root)->right, item, cmpf);
}
