/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_get_v_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 21:19:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 21:21:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		lm_get_vtexel(t_lm *lm)
{
	t_mesh *mesh;

	mesh = lm->mesh;
	mesh->flag |= SCOP_VT;
	if (sscanf(lm->line, "%s %f %f\n", lm->type, &lm->buffer_vt[0],
			&lm->buffer_vt[1]) != 3)
	{
		return (false);
	}
	lm->vt[2 * lm->nb_vt + 0] = lm->buffer_vt[0];
	lm->vt[2 * lm->nb_vt + 1] = lm->buffer_vt[1];
	lm->nb_vt++;
	return (true);
}

bool		lm_get_vnormal(t_lm *lm)
{
	t_mesh *mesh;

	mesh = lm->mesh;
	mesh->flag |= SCOP_VN;
	if (sscanf(lm->line, "%s %f %f %f\n", lm->type, &lm->buffer_vn[0],
			&lm->buffer_vn[1], &lm->buffer_vn[2]) != 4)
	{
		return (false);
	}
	lm->vn[3 * lm->nb_vn + 0] = lm->buffer_vn[0];
	lm->vn[3 * lm->nb_vn + 1] = lm->buffer_vn[1];
	lm->vn[3 * lm->nb_vn + 2] = lm->buffer_vn[2];
	lm->nb_vn++;
	return (true);
}

static void	lm_min_max_vertex(t_model *model, float v[4])
{
	if (v[0] > model->max.x)
		model->max.x = v[0];
	else if (v[0] < model->min.x)
		model->min.x = v[0];
	else if (v[1] > model->max.y)
		model->max.y = v[1];
	else if (v[1] < model->min.y)
		model->min.y = v[1];
	else if (v[2] > model->max.z)
		model->max.z = v[2];
	else if (v[2] < model->min.z)
		model->min.z = v[2];
}

bool		lm_get_vertex(t_lm *lm)
{
	t_mesh *mesh;

	mesh = lm->mesh;
	mesh->flag |= SCOP_V;
	if (sscanf(lm->line, "%s %f %f %f\n", lm->type, &lm->buffer_v[0],
			&lm->buffer_v[1], &lm->buffer_v[2]) != 4)
	{
		return (false);
	}
	lm->v[3 * lm->nb_v + 0] = lm->buffer_v[0];
	lm->v[3 * lm->nb_v + 1] = lm->buffer_v[1];
	lm->v[3 * lm->nb_v + 2] = lm->buffer_v[2];
	lm->nb_v++;
	lm_min_max_vertex(lm->model, lm->buffer_v);
	return (true);
}
