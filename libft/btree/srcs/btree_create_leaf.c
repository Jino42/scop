/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_leaf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 22:05:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/08/14 11:26:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_btree	*btree_create_leaf(void *content)
{
	t_btree *ptr;

	ptr = NULL;
	if (!(ptr = ft_memalloc(sizeof(t_btree))))
		return (NULL);
	ptr->left = NULL;
	ptr->right = NULL;
	ptr->content = content;
	return (ptr);
}
