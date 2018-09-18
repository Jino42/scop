/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_light_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 18:11:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 18:34:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			light_uniform(t_scene *scene, t_light *light,
									t_shader *shader, t_model *model)
{
	t_matrix	mvp;
	t_matrix	temp;

	temp = matrix_get_mult_matrix(&light->transform, &scene->cam->view);
	mvp = matrix_get_mult_matrix(&temp, &scene->cam->projection);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "V"),
			1, GL_FALSE, &scene->cam->view.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "P"),
			1, GL_FALSE, &scene->cam->projection.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "M"),
			1, GL_FALSE, &model->transform.matrix[0][0]);
}

static t_model		*light_pick_model(t_scene *scene, t_light *light)
{
	if (light->flag & LIGHT_BASIC)
		return (scene->m_model_hidden->model[MODEL_INDEX_LIGHT_BASIC]);
	else if (light->flag & LIGHT_DIRECTIONNAL)
		return (scene->m_model_hidden->model[MODEL_INDEX_LIGHT_DIRECTIONNAL]);
	else if (light->flag & LIGHT_POINT)
		return (scene->m_model_hidden->model[MODEL_INDEX_LIGHT_POINT]);
	else if (light->flag & LIGHT_SPOT)
		return (scene->m_model_hidden->model[MODEL_INDEX_LIGHT_SPOT]);
	return (NULL);
}

static void			light_render(t_model *model, t_shader *shader)
{
	t_m_mesh	*m_mesh;
	uint32_t	i;

	shader->use(shader);
	m_mesh = model->m_mesh;
	i = 0;
	while (i < m_mesh->size)
	{
		glBindVertexArray(m_mesh->mesh[i]->VAO);
		glDrawElements(GL_TRIANGLES, m_mesh->mesh[i]->nb_indices,
						GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		i++;
	}
}

bool				m_light_render(t_scene *scene)
{
	t_light		*light;
	t_model		*model;
	t_shader	*shader;
	uint32_t	i;

	shader = scene->m_shader_hidden->shader[SHADER_INDEX_LIGHT];
	i = 0;
	while (i < scene->m_light->size)
	{
		light = scene->m_light->light[i];
		if (!(model = light_pick_model(scene, light)))
			return (NULL);
		glPolygonMode(GL_FRONT, model->type_draw);
		shader->use(shader);
		if (light->update)
			light_compute_transform(light, model);
		light_uniform(scene, light, shader, model);
		light_render(model, shader);
		glUseProgram(0);
		i++;
	}
	return (true);
}
