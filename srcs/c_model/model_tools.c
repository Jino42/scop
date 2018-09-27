/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:49:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/26 18:28:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			model_gen_gl_buffers(t_model *model)
{
	unsigned int	i;

	i = 0;
	model->flag = model->m_mesh->mesh[i]->flag;
	model->flag |= SCOP_VN;
	while (i < model->m_mesh->size)
	{
		mesh_gen_gl_buffers(model->m_mesh->mesh[i]);
		model->nb_indices += model->m_mesh->mesh[i]->nb_indices;
		model->same_indices += model->m_mesh->mesh[i]->same_indices;
		i++;
	}
}

void			model_setup_scaling(t_model *model)
{
	t_vector	diff;
	float		scaling;

	diff = vector_get_sub(&model->min, &model->max);
	diff = vector_get_abs(&diff);
	if (diff.x > diff.y && diff.x > diff.z)
		scaling = 1.f / diff.x;
	else if (diff.y > diff.x && diff.y > diff.z)
		scaling = 1.f / diff.y;
	else
		scaling = 1.f / diff.z;
	model->min = vector_get_invert(&model->min);
	diff = vector_get_sub(&model->max, &model->min);
	diff.x = model->max.x - model->min.x;
	diff.y = model->max.y - model->min.y;
	diff.z = model->max.z - model->min.z;
	model->inter_scaling = scaling;
	diff = vector_get_mult(&diff, 0.5f);
	model->center = diff;
	model->negative_center = vector_get_invert(&diff);
	model_compute_transform(model);
}

static t_vector	model_get_translation(t_model *model)
{
	t_vector	scaling;
	float		same_scaling;
	t_vector	negative_trans;

	if (model->flag & MODEL_SAME_SCALING)
	{
		same_scaling = model->inter_scaling * model->same_scaling;
		matrix_scaling(&model->transform, same_scaling);
		negative_trans = vector_get_mult(&model->negative_center,
					model->inter_scaling * model->same_scaling);
	}
	else
	{
		scaling = vector_get_mult(&model->scaling, model->inter_scaling);
		negative_trans = vector_get_scale(&model->negative_center, &scaling);
		matrix_vector_scaling(&model->transform, &scaling);
	}
	return (negative_trans);
}

void			model_compute_transform(t_model *model)
{
	t_vector	negative_trans;
	t_vector	trans;

	matrix_identity(&model->transform);
	negative_trans = model_get_translation(model);
	trans = vector_get_invert(&negative_trans);
	matrixgl_translation(&model->transform, &negative_trans);
	matrixgl_rotation_y(&model->transform, model->rotation.y);
	matrixgl_rotation_z(&model->transform, model->rotation.z);
	matrixgl_rotation_x(&model->transform, model->rotation.x);
	matrixgl_translation(&model->transform, &trans);
	matrixgl_translation(&model->transform, &model->position);
}

void			model_update(t_model *model)
{
	model->update = false;
	model_compute_transform(model);
}
