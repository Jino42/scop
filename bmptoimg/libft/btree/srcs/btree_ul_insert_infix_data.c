/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_ul_insert_infix_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 11:26:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/16 11:27:00 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		btree_ul_insert_infix_data(t_btree **root, void *item,
		size_t (*cmpf)(void *, void *))
{
	if (!*root)
	{
		*root = btree_create_leaf(item);
		return ;
	}
	if (cmpf(item, (*root)->content) <= 0)
		btree_ul_insert_infix_data(&(*root)->left, item, cmpf);
	else
		btree_ul_insert_infix_data(&(*root)->right, item, cmpf);
}
