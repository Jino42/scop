/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_indexing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 21:11:23 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 21:30:54 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	lm_indexing_same(t_lm *lm, t_mesh *mesh, const int sommet)
{
	int		i;

	i = mesh->nb_indices - 100;
	if (i < 0)
		i = 0;
	while (i < mesh->nb_indices)
	{
		if (equal3f(&mesh->indexed_v[i * 3],
				&lm->v[(lm->buffer_index_v[sommet] - 1) * 3])
			&& equal2f(&mesh->indexed_vt[i * 2],
				&lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2])
			&& equal3f(&mesh->indexed_vn[i * 3],
				&lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3]))
		{
			return (i);
		}
		i++;
	}
	return (0);
}

static void	lm_indexing_memcpy(t_lm *lm, t_mesh *mesh, const int sommet)
{
	if (mesh->flag & SCOP_V)
	{
		memcpy(&mesh->indexed_v[mesh->nb_indices * 3],
			&lm->v[(lm->buffer_index_v[sommet] - 1) * 3],
			3 * sizeof(GLfloat));
	}
	if (mesh->flag & SCOP_VT)
	{
		memcpy(&mesh->indexed_vt[mesh->nb_indices * 2],
			&lm->vt[(lm->buffer_index_vt[sommet] - 1) * 2],
			2 * sizeof(GLfloat));
	}
	if (mesh->flag & SCOP_VN)
	{
		memcpy(&mesh->indexed_vn[mesh->nb_indices * 3],
			&lm->vn[(lm->buffer_index_vn[sommet] - 1) * 3],
			3 * sizeof(GLfloat));
	}
}

static void	lm_indexing(t_lm *lm, t_mesh *mesh, const int sommet)
{
	float	nb;
	int		indice;

	if (lm->scene->flag & SCOP_INDEXING
		&& mesh->flag & (SCOP_V | SCOP_VT | SCOP_VN))
	{
		if ((indice = lm_indexing_same(lm, mesh, sommet)))
		{
			mesh->indices[mesh->nb_indices + mesh->same_indices] = indice;
			mesh->same_indices++;
			return ;
		}
	}
	mesh->indices[mesh->nb_indices + mesh->same_indices] = mesh->nb_indices;
	lm_indexing_memcpy(lm, mesh, sommet);
	nb = (float)rand() / (float)RAND_MAX;
	mesh->indexed_color[mesh->nb_indices] =
		nb - (((int)(nb * 100.f)) % 10 / 100.f);
	mesh->nb_indices++;
}

static void	lm_indexing_face_increment(t_mesh *mesh)
{
	if (!(mesh->flag & SCOP_VN))
		lm_indexing_calculate_normal(mesh);
	if (!(mesh->flag & SCOP_VT))
		lm_indexing_calculate_vt(mesh);
	mesh->nb_faces++;
}

bool		lm_indexing_face(t_lm *lm, t_mesh *mesh, const int sommet4)
{
	int sommet;

	sommet = 0;
	while (sommet < 3)
	{
		lm_indexing(lm, mesh, sommet);
		sommet++;
	}
	lm_indexing_face_increment(mesh);
	if (sommet4 == 4)
	{
		sommet = 0;
		while (sommet < 4)
		{
			if (sommet == 1)
				sommet++;
			lm_indexing(lm, mesh, sommet);
			sommet++;
		}
		lm_indexing_face_increment(mesh);
	}
	return (true);
}
