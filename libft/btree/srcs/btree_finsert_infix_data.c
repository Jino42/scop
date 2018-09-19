/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_finsert_infix_data.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:01:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/18 15:18:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		btree_finsert_infix_data(t_btree **root, void *item,
		float (*cmpf)(void *, void *))
{
	if (!*root)
	{
		*root = btree_create_leaf(item);
		return ;
	}
	if (cmpf(item, (*root)->content) <= 0)
		btree_finsert_infix_data(&(*root)->left, item, cmpf);
	else
		btree_finsert_infix_data(&(*root)->right, item, cmpf);
}
