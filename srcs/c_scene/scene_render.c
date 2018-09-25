/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:38:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 19:18:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		scene_set_uniform_time(t_scene *scene,
										t_shader *shader,
										t_model *model,
										float time)
{
	glUniform1f(glGetUniformLocation(shader->program, "u_time"), time);
	glUniform1i(glGetUniformLocation(shader->program, "u_timestamp"), scene->timestamp);
	glUniform1i(glGetUniformLocation(shader->program, "u_model_timestamp"), model->timestamp);
}

static void	scene_set_uniform_lights_basique(t_light *light,
												t_shader *shader,
												unsigned int i)
{
	char			buffer[255];

	sprintf(buffer, "u_light[%i].ambient", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->ambient);
	sprintf(buffer, "u_light[%i].diffuse", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->diffuse);
	sprintf(buffer, "u_light[%i].specular", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->specular);
	sprintf(buffer, "u_light[%i].position", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->position);
	sprintf(buffer, "u_light[%i].direction", i);
	glUniform3fv(glGetUniformLocation(shader->program, buffer), 1,
		(GLfloat *)&light->direction);
		sprintf(buffer, "u_light[%i].intensity", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->intensity);
}

static void	scene_set_uniform_lights_complex(t_light *light,
												t_shader *shader,
												unsigned int i)
{
	char			buffer[255];

	sprintf(buffer, "u_light[%i].constent", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->constent);
	sprintf(buffer, "u_light[%i].linear", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->linear);
	sprintf(buffer, "u_light[%i].quadratic", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->quadratic);
	sprintf(buffer, "u_light[%i].spot_little_radius", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->spot_little_radius);
	sprintf(buffer, "u_light[%i].spot_big_radius", i);
	glUniform1f(glGetUniformLocation(shader->program, buffer),
		light->spot_big_radius);
	sprintf(buffer, "u_light[%i].type", i);
	glUniform1i(glGetUniformLocation(shader->program, buffer),
		light->flag & 0xFF);
}

void		scene_set_uniform_lights(t_m_light *m_light, t_shader *shader)
{
	unsigned int	i;

	i = 0;
	while (i < m_light->size)
	{
		scene_set_uniform_lights_basique(m_light->light[i], shader, i);
		scene_set_uniform_lights_complex(m_light->light[i], shader, i);
		i++;
	}
}

void		scene_set_uniform_material(t_shader *shader,
										t_material *material)
{
	glUniform3fv(glGetUniformLocation(shader->program, "u_material.ambient"),
		1, (GLfloat *)&material->ambient);
	glUniform3fv(glGetUniformLocation(shader->program, "u_material.diffuse"),
		1, (GLfloat *)&material->diffuse);
	glUniform3fv(glGetUniformLocation(shader->program, "u_material.specular"),
		1, (GLfloat *)&material->specular);
	glUniform1f(glGetUniformLocation(shader->program, "u_material.shininess"),
		material->shininess);
	glUniform1f(glGetUniformLocation(shader->program, "u_material.flag"),
		material->flag);
}

void		scene_set_uniform_material_personnal(t_shader *shader,
										t_material *material_personnal)
{
	glUniform3fv(glGetUniformLocation(shader->program,
		"u_material_personnal.ambient"), 1,
		(GLfloat *)&material_personnal->ambient);
	glUniform3fv(glGetUniformLocation(shader->program,
		"u_material_personnal.diffuse"), 1,
		(GLfloat *)&material_personnal->diffuse);
	glUniform3fv(glGetUniformLocation(shader->program,
		"u_material_personnal.specular"), 1,
		(GLfloat *)&material_personnal->specular);
	glUniform1f(glGetUniformLocation(shader->program,
		"u_material_personnal.shininess"), material_personnal->shininess);
	glUniform1f(glGetUniformLocation(shader->program,
		"u_material_personnal.flag"), material_personnal->flag);
}

void		scene_set_uniform_texture_dynamique(t_scene *scene, t_shader *shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, scene->rbo->texture_color_buffer);
	glUniform1i(glGetUniformLocation(shader->program, "u_texture_dynamique"), 0);
}

void		scene_set_uniform_texture_personnal(t_shader *shader, t_material *material_personnal)
{
	if (material_personnal->flag & MATERIAL_MAP_DIFFUSE)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, material_personnal->texture_diffuse);
		glUniform1i(glGetUniformLocation(shader->program, "u_texture_personnal"), 1);
		glUniform1i(glGetUniformLocation(shader->program, "u_material_personnal.texture_diffuse"), 1);
	}
	else
		glUniform1i(glGetUniformLocation(shader->program, "u_material_personnal.texture_diffuse"), 0);
}

void		scene_set_uniform_texture_basic(t_shader *shader, t_model *model, t_material *material)
{
	if (model->flag & MODEL_USE_TEXTURE && material->flag & MATERIAL_MAP_DIFFUSE)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, material->texture_diffuse);
		glUniform1i(glGetUniformLocation(shader->program, "u_texture"), 2);
	}
}

void		scene_render(t_scene *scene, float time)
{
	t_material *material;
	t_material *material_personnal;
	t_m_mesh *m_mesh;
	t_model	*model;
	t_shader	*shader;
	t_matrix temp, mvp;

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_STENCIL_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glPointSize(5.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilMask (0xFF);
	glDepthFunc (GL_LESS);

	for (unsigned int i = 0; i < scene->m_model->size; i++)
	{
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		model = scene->m_model->model[i];

		shader = scene->m_shader->shader[model->index_shader];

		m_mesh = model->m_mesh;
		glPolygonMode(GL_FRONT_AND_BACK, model->type_draw);

		if (model->update)
			model_update(model);
		shader->use(shader);

		material = scene->m_material->material[model->index_material];
		scene_set_uniform_material(shader, material);

		temp = matrix_get_mult_matrix(&model->transform, &scene->cam->view);
		mvp = matrix_get_mult_matrix(&temp, &scene->cam->projection);

		scene_set_uniform_time(scene, shader, model, time);
		scene_set_uniform_lights(scene->m_light, shader);

		glUniform3f(glGetUniformLocation(shader->program, "u_cameraPosition"), scene->cam->position.x, scene->cam->position.y, scene->cam->position.z);

		glUniformMatrix4fv(glGetUniformLocation(shader->program, "MVP"), 1, GL_FALSE, &mvp.matrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "V"), 1, GL_FALSE, &scene->cam->view.matrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "P"), 1, GL_FALSE, &scene->cam->projection.matrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "M"), 1, GL_FALSE, &model->transform.matrix[0][0]);

		glUniform1i(glGetUniformLocation(shader->program, "u_obj_flag"), model->flag);
		glUniform1i(glGetUniformLocation(shader->program, "u_obj_last_flag"), model->last_flag);

		uint32_t i = 0;
		while (i < m_mesh->size)
		{
			material_personnal = scene->m_material_personnal->material[m_mesh->mesh[i]->index_material_personnal];
			scene_set_uniform_texture_dynamique(scene, shader);
			scene_set_uniform_texture_personnal(shader, material_personnal);
			scene_set_uniform_texture_basic(shader, model, material);

			scene_set_uniform_material_personnal(shader, material_personnal);

			glBindVertexArray(m_mesh->mesh[i]->vao);
			glDrawElements(GL_TRIANGLES, m_mesh->mesh[i]->nb_indices + m_mesh->mesh[i]->same_indices, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, m_mesh->mesh[i]->nb_indices);
			glBindVertexArray(0);
			i++;
		}
		glUseProgram(0);
	}

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	m_light_render(scene);
}
