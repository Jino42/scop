/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_uniform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:55:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 20:05:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		scene_set_uniform_time(t_scene *scene,
										t_shader *shader,
										t_model *model,
										float time)
{
	glUniform1f(glGetUniformLocation(shader->program,
		"u_time"), time);
	glUniform1i(glGetUniformLocation(shader->program,
		"u_timestamp"), scene->timestamp);
	glUniform1i(glGetUniformLocation(shader->program,
		"u_model_timestamp"), model->timestamp);
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

void		scene_set_uniform_data(t_scene *scene,
										t_shader *shader,
										t_model *model)
{
	t_matrix	temp;
	t_matrix	mvp;

	temp = matrix_get_mult_matrix(&model->transform, &scene->cam->view);
	mvp = matrix_get_mult_matrix(&temp, &scene->cam->projection);
	glUniform3f(glGetUniformLocation(shader->program, "u_cameraPosition"),
		scene->cam->position.x, scene->cam->position.y, scene->cam->position.z);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "MVP"),
		1, GL_FALSE, &mvp.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "V"),
		1, GL_FALSE, &scene->cam->view.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "P"),
		1, GL_FALSE, &scene->cam->projection.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "M"),
		1, GL_FALSE, &model->transform.matrix[0][0]);
	glUniform1i(glGetUniformLocation(shader->program, "u_obj_flag"),
		model->flag);
	glUniform1i(glGetUniformLocation(shader->program, "u_obj_last_flag"),
		model->last_flag);
}
