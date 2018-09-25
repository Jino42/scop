/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_check_realloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 21:22:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 21:29:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	lm_check_realloc_buffer(t_lm *lm)
{
	if ((lm->nb_v + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_v)
	{
		lm->mem_len_v += BUFFER_OBJ * sizeof(GLfloat);
		if (!(lm->v = realloc(lm->v, lm->mem_len_v)))
			return (false);
	}
	if ((lm->nb_vt + 6) * sizeof(GLfloat) * 2 >= lm->mem_len_vt)
	{
		lm->mem_len_vt += BUFFER_OBJ * sizeof(GLfloat);
		if (!(lm->vt = realloc(lm->vt, lm->mem_len_vt)))
			return (false);
	}
	if ((lm->nb_vn + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_vn)
	{
		lm->mem_len_vn += BUFFER_OBJ * sizeof(GLfloat);
		if (!(lm->vn = realloc(lm->vn, lm->mem_len_vn)))
			return (false);
	}
	return (true);
}

static bool	lm_check_realloc_v_data(t_lm *lm, t_mesh *mesh)
{
	if ((mesh->nb_indices + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_indexed_v)
	{
		lm->mem_len_indexed_v += BUFFER_OBJ * sizeof(GLfloat);
		mesh->indexed_v = realloc(mesh->indexed_v, lm->mem_len_indexed_v);
		if (!mesh->indexed_v)
			return (false);
	}
	if ((mesh->nb_indices + 6) * sizeof(GLfloat) * 2 >= lm->mem_len_indexed_vt)
	{
		lm->mem_len_indexed_vt += BUFFER_OBJ * sizeof(GLfloat);
		mesh->indexed_vt = realloc(mesh->indexed_vt, lm->mem_len_indexed_vt);
		if (!mesh->indexed_vt)
			return (false);
	}
	if ((mesh->nb_indices + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_indexed_vn)
	{
		lm->mem_len_indexed_vn += BUFFER_OBJ * sizeof(GLfloat);
		mesh->indexed_vn = realloc(mesh->indexed_vn, lm->mem_len_indexed_vn);
		if (!mesh->indexed_vn)
			return (false);
	}
	return (true);
}

bool		lm_check_realloc(t_lm *lm)
{
	t_mesh *mesh;

	mesh = lm->mesh;
	if ((mesh->nb_indices + mesh->same_indices + 18) * sizeof(GLuint)
			>= lm->mem_len_indices)
	{
		lm->mem_len_indices += BUFFER_OBJ * sizeof(GLuint);
		mesh->indices = realloc(mesh->indices, lm->mem_len_indices);
	}
	if ((mesh->nb_indices + 6) * sizeof(GLfloat) >= lm->mem_len_indexed_color)
	{
		lm->mem_len_indexed_color += BUFFER_OBJ * sizeof(GLfloat);
		mesh->indexed_color =
			realloc(mesh->indexed_color, lm->mem_len_indexed_color);
	}
	if ((mesh->nb_indices + 6) * sizeof(GLfloat) * 3 >= lm->mem_len_indexed_u)
	{
		lm->mem_len_indexed_u += BUFFER_OBJ * sizeof(GLfloat);
		mesh->indexed_u = realloc(mesh->indexed_u, lm->mem_len_indexed_u);
	}
	if (!mesh->indexed_u || !mesh->indexed_color || !mesh->indices
		|| !lm_check_realloc_buffer(lm)
		|| !lm_check_realloc_v_data(lm, mesh))
		return (false);
	return (true);
}
