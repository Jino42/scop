/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:38:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 20:10:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	scene_render_mesh(t_scene *scene,
								t_shader *shader,
								t_model *model,
								t_material *material)
{
	t_material	*material_personnal;
	t_m_mesh	*m_mesh;
	uint32_t	i;

	m_mesh = model->m_mesh;
	i = 0;
	while (i < m_mesh->size)
	{
		material_personnal = scene->m_material_personnal->material[\
			m_mesh->mesh[i]->index_material_personnal];
		scene_set_uniform_texture_dynamique(scene, shader);
		scene_set_uniform_texture_personnal(shader, material_personnal);
		scene_set_uniform_texture_basic(shader, model, material);
		scene_set_uniform_material_personnal(shader, material_personnal);
		glBindVertexArray(m_mesh->mesh[i]->vao);
		glDrawElements(GL_TRIANGLES,
			m_mesh->mesh[i]->nb_indices + m_mesh->mesh[i]->same_indices,
			GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		i++;
	}
}

static void	scene_render_set_params(void)
{
	glEnable(GL_DEPTH_TEST);
	glPointSize(5.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glDepthFunc(GL_LESS);
}

void		scene_render(t_scene *scene, float time)
{
	t_material		*material;
	t_model			*model;
	t_shader		*shader;
	unsigned int	i;

	scene_render_set_params();
	i = 0;
	while (i < scene->m_model->size)
	{
		model = scene->m_model->model[i];
		glPolygonMode(GL_FRONT_AND_BACK, model->type_draw);
		shader = scene->m_shader->shader[model->index_shader];
		if (model->update)
			model_update(model);
		shader->use(shader);
		material = scene->m_material->material[model->index_material];
		scene_set_uniform_material(shader, material);
		scene_set_uniform_time(scene, shader, model, time);
		scene_set_uniform_lights(scene->m_light, shader);
		scene_set_uniform_data(scene, shader, model);
		scene_render_mesh(scene, shader, model, material);
		glUseProgram(0);
		i++;
	}
	m_light_render(scene);
}
