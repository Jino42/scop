/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 22:30:43 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/09 22:32:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

size_t		btree_size(t_btree *bt)
{
	if (!bt)
		return (0);
	return (1 + btree_size(btree_child_left(bt))
			+ btree_size(btree_child_right(bt)));
}
