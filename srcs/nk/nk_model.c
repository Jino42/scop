/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_model.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 22:38:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 23:35:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

static void			nk_model_scaling(t_nk *nk, t_model *model)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	model->update = true;
	nk_layout_row_static(ctx, 25, 120, 2);
	nk_label(ctx, "Same XYZ Scaling", NK_TEXT_LEFT);
	nk_check(nk, &model->flag, MODEL_SAME_SCALING, "Inactive");
	nk_layout_row_static(ctx, 25, 300, 1);
	if (!(model->flag & MODEL_SAME_SCALING))
		nk_combo_vector(nk, &model->scaling, "Scaling");
	else
	{
		nk_property_float(ctx, "Scaling", FLOAT_MIN, &model->same_scaling,
			FLT_MAX, 0.1f, 0.05f);
	}
}

static void			nk_model_type_draw(struct nk_context *ctx, t_model *model)
{
	nk_layout_row_static(ctx, 30, 80, 3);
	model->type_draw = nk_option_label(ctx, "GL_POINT",
		model->type_draw == GL_POINT) ? GL_POINT : model->type_draw;
	model->type_draw = nk_option_label(ctx, "GL_LINE",
		model->type_draw == GL_LINE) ? GL_LINE : model->type_draw;
	model->type_draw = nk_option_label(ctx, "GL_FILL",
		model->type_draw == GL_FILL) ? GL_FILL : model->type_draw;
}

static void			nk_model_material(t_scene *scene, t_nk *nk,
									struct nk_context *ctx, t_model *model)
{
	nk_check(nk, &model->flag, MODEL_USE_MATERIAL_PERSONNAL, "Personnal");
	if (!(model->flag & MODEL_USE_MATERIAL_PERSONNAL))
	{
		model->index_material = nk_combo(ctx,
								(const char **)scene->m_material->material_name,
								scene->m_material->size,
								model->index_material,
								25, nk_vec2(200, 200));
	}
}

void				nk_model(t_nk *nk, t_scene *scene, t_model *model)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	model->update = true;
	nk_layout_row_static(ctx, 25, 300, 1);
	nk_combo_vector(nk, &model->position, "Position");
	nk_layout_row_static(ctx, 25, 300, 1);
	nk_combo_vector(nk, &model->rotation, "Rotation");
	nk_model_scaling(nk, model);
	nk_model_type_draw(ctx, model);
	nk_layout_row_static(ctx, 25, 150, 1);
	model->index_shader = nk_combo(ctx,
							(const char **)scene->m_shader->shader_name,
							scene->m_shader->size,
							model->index_shader,
							25, nk_vec2(200, 200));
	nk_model_material(scene, nk, ctx, model);
	nk_check(nk, &model->flag, MODEL_USE_DYNAMIQUE_TEXTURE,
				"Dynamique texture");
	nk_check(nk, &model->flag, MODEL_ROTATE, "Rotate");
}
