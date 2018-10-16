/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_model_material_flag.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:42:43 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 17:04:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			nk_model_material_flag_set(t_model *model, int set)
{
	model->flag |= set;
	if (set != MODEL_USE_MATERIAL_PERSONNAL
		&& model->flag & MODEL_USE_MATERIAL_PERSONNAL)
	{
		model->flag ^= MODEL_USE_MATERIAL_PERSONNAL;
	}
	if (set != MODEL_USE_BASIC
		&& model->flag & MODEL_USE_BASIC)
	{
		model->flag ^= MODEL_USE_BASIC;
	}
	if (set != MODEL_USE_TEXTURE
		&& model->flag & MODEL_USE_TEXTURE)
	{
		model->flag ^= MODEL_USE_TEXTURE;
	}
}

static void			nk_model_material_flag_time_transition(t_scene *scene,
															t_model *model)
{
	if ((model->flag & MODEL_USE_FLAG)
		!= (model->temp_flag & MODEL_USE_FLAG))
	{
		if ((model->temp_flag & MODEL_USE_FLAG)
			!= (model->last_flag & MODEL_USE_FLAG))
			model->last_flag = model->flag;
		model->timestamp = scene->timestamp;
		model->temp_flag = model->flag;
	}
	if ((model->flag & MODEL_USE_FLAG)
		!= (model->last_flag & MODEL_USE_FLAG))
	{
		if (scene->timestamp - model->timestamp >= TEXTURE_TRANSITION)
			model->last_flag = model->flag;
	}
}

void				nk_model_material_flag(t_nk *nk,
											t_scene *scene,
											t_model *model)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if ((scene->m_material->material[model->index_material]->flag \
		& MATERIAL_MAP_DIFFUSE)
		&& nk_option_label(ctx, "MODEL_USE_TEXTURE",
			model->flag & MODEL_USE_TEXTURE))
	{
		nk_model_material_flag_set(model, MODEL_USE_TEXTURE);
	}
	if (nk_option_label(ctx, "MODEL_USE_MATERIAL_PERSONNAL",
		model->flag & MODEL_USE_MATERIAL_PERSONNAL))
	{
		nk_model_material_flag_set(model, MODEL_USE_MATERIAL_PERSONNAL);
	}
	if (nk_option_label(ctx, "MODEL_USE_BASIC", model->flag & MODEL_USE_BASIC))
		nk_model_material_flag_set(model, MODEL_USE_BASIC);
	nk_model_material_flag_time_transition(scene, model);
}
