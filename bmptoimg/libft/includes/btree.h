/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 18:02:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 21:35:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include "../../libft/includes/ft_printf.h"

typedef struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*content;
}				t_btree;

t_btree			*btree_create_node(void *content, t_btree *btree_left,
		t_btree *right);
t_btree			*btree_create_leaf(void *content);

t_btree			*btree_child_left(t_btree *btree);
t_btree			*btree_child_right(t_btree *btree);

int				btree_is_empty(t_btree *btree);
int				btree_is_leaf(t_btree *btree);

size_t			btree_size(t_btree *bt);

void			btree_insert_right(t_btree *node, void *item);
void			btree_insert_left(t_btree *node, void *item);

void			*btree_delete_right(t_btree *node);
void			*btree_delete_left(t_btree *node);

void			btree_depth_insert_right(t_btree *node, void *item);
void			btree_depth_insert_left(t_btree *node, void *item);

void			btree_apply_prefix(t_btree *node, void (*apply)(void *));
void			btree_apply_infix(t_btree *node, void (*apply)(void *));
void			btree_apply_suffix(t_btree *node, void (*apply)(void *));
void			btree_env_apply_infix(void *env, t_btree *node,
										void (*apply)(void *, void *));

void			btree_apply_free(t_btree *node, void (*apply)(void *));

void			btree_insert_data(t_btree **root, void *item,
		int (*cmpf)(void *, void*));
void			*btree_search_item(t_btree *root, void *ref,
		int (*cmpf)(void *, void *));

void			btree_insert_infix_data(t_btree **root, void *item,
		int (*cmpf)(void *, void*));
void			btree_ul_insert_infix_data(t_btree **root, void *item,
		size_t (*cmpf)(void *, void*));
void			btree_finsert_infix_data(t_btree **root, void *item,
		float (*cmpf)(void *, void *));

#endif
