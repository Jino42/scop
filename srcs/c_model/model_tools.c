/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:49:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:53:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		model_gen_gl_buffers(t_model *model)
{
	unsigned int	i;

	i = 0;
	while (i < model->m_mesh->size)
	{
		mesh_gen_gl_buffers(model->m_mesh->mesh[i]);
		i++;
	}
}

void		model_setup_scaling(t_model *model)
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
	model->inter_scaling = scaling;
	diff = vector_construct(0.f, -0.5f, 0.f);
	vector_add(&model->position, &diff);
	model->center = diff;
	model->negative_center = vector_get_invert(&diff);
	model_compute_transform(model);
}

void		model_compute_transform(t_model *model)
{
	t_vector	scaling;
	float		same_scaling;

	matrix_identity(&model->transform);
	if (model->flag & MODEL_SAME_SCALING)
	{
		same_scaling = model->inter_scaling * model->same_scaling;
		matrix_scaling(&model->transform, same_scaling);
	}
	else
	{
		scaling = vector_get_mult(&model->scaling, model->inter_scaling);
		matrix_vector_scaling(&model->transform, &scaling);
	}
	matrixgl_rotation_x(&model->transform, model->rotation.x);
	matrixgl_rotation_y(&model->transform, model->rotation.y);
	matrixgl_rotation_z(&model->transform, model->rotation.z);
	matrixgl_translation(&model->transform, &model->position);
}

void		model_update(t_model *model)
{
	model->update = false;
	model_compute_transform(model);
}
