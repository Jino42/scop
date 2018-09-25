/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_indexing_calculate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 21:12:27 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 21:14:57 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_vector		vector_calculate_normal(t_vector *a,
											t_vector *b,
											t_vector *c)
{
	t_vector normal;
	t_vector u;
	t_vector v;

	u = vector_get_sub(b, a);
	v = vector_get_sub(c, a);
	normal = vector_get_cross_product(&u, &v);
	return (vector_get_normalize(&normal));
}

void				lm_indexing_calculate_normal(t_mesh *mesh)
{
	t_vector	calc_normal;
	t_vector	a;
	t_vector	b;
	t_vector	c;
	t_vector3f	set;

	*((t_vector3f*)&a) =
		((t_vector3f*)mesh->indexed_v)[mesh->nb_indices - 1];
	*((t_vector3f*)&b) =
		((t_vector3f*)mesh->indexed_v)[mesh->nb_indices - 2];
	*((t_vector3f*)&c) =
		((t_vector3f*)mesh->indexed_v)[mesh->nb_indices - 3];
	calc_normal = vector_calculate_normal(&c, &b, &a);
	set = *((t_vector3f *)&calc_normal);
	((t_vector3f*)mesh->indexed_vn)[(mesh->nb_indices - 1)] = set;
	((t_vector3f*)mesh->indexed_vn)[(mesh->nb_indices - 2)] = set;
	((t_vector3f*)mesh->indexed_vn)[(mesh->nb_indices - 3)] = set;
}

void				lm_indexing_calculate_vt(t_mesh *mesh)
{
	t_vector	b;
	t_vector	c;
	t_vector3f	set;
	t_vector	u;

	*((t_vector3f*)&b) =
		((t_vector3f*)mesh->indexed_v)[mesh->nb_indices - 2];
	*((t_vector3f*)&c) =
		((t_vector3f*)mesh->indexed_v)[mesh->nb_indices - 3];
	u = vector_get_sub(&b, &c);
	vector_normalize(&u);
	set = *((t_vector3f *)&u);
	((t_vector3f *)mesh->indexed_u)[mesh->nb_indices - 3] = set;
	((t_vector3f *)mesh->indexed_u)[mesh->nb_indices - 2] = set;
	((t_vector3f *)mesh->indexed_u)[mesh->nb_indices - 1] = set;
}
