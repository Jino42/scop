#include "scop.h"

void		scene_render(t_scene *scene)
{
	t_vector ambient = vector_construct(0.0215f, 0.1745f, 0.0215f);
	t_vector diffuse = vector_construct(0.07568f, 0.61424f, 0.07568f);;
	t_vector specular = vector_construct(0.633f, 0.727811f, 0.633f);
	float	shininess = 76.8f;

	t_vector lambient = vector_construct(0.9f, 0.9f, 0.9f);
	t_vector ldiffuse = vector_construct(0.70f, 0.70f, 0.70f);;
	t_vector lspecular = vector_construct(1.f, 1.f, 1.f);
	t_vector lposition = vector_construct(0.3f, 0.3f, 0.3f);
	t_m_mesh *m_mesh;
	t_model	*model;
	t_shader	*shader;
	t_matrix temp, mvp;

	shader = scene->m_shader->shader[0];
	for (unsigned int i = 0; i < scene->m_model->size; i++)
	{
		model = scene->m_model->model[i];
		m_mesh = model->m_mesh;
		glPolygonMode(GL_FRONT_AND_BACK, model->type_draw);

		if (model->update)
			model_update(model);

		shader->use(shader);
		temp = matrix_get_mult_matrix(&model->transform, &scene->cam->view);
		mvp = matrix_get_mult_matrix(&temp, &scene->cam->projection);
		glUniform3fv(
				glGetUniformLocation(shader->program, "light.ambient"),
				1,
				(GLfloat *)&lambient);
		glUniform3fv(
				glGetUniformLocation(shader->program, "light.diffuse"),
				1,
				(GLfloat *)&ldiffuse);
		glUniform3fv(
				glGetUniformLocation(shader->program, "light.specular"),
				1,
				(GLfloat *)&lspecular);
		glUniform3fv(
				glGetUniformLocation(shader->program, "light.position"),
				1,
				(GLfloat *)&lposition);
		glUniform3f(
				glGetUniformLocation(shader->program, "cameraPosition"),
				scene->cam->position.x,
				scene->cam->position.y,
				scene->cam->position.z);
		glUniform3f(
				glGetUniformLocation(shader->program, "camDir"),
				scene->cam->to.x,
				scene->cam->to.y,
				scene->cam->to.z);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "MVP"),
				1, GL_FALSE, &mvp.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "V"),
				1, GL_FALSE, &scene->cam->view.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "P"),
				1, GL_FALSE, &scene->cam->projection.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "M"),
				1, GL_FALSE, &model->transform.matrix[0][0]);
		uint32_t i = 0;
		while (i < m_mesh->size)
		{
			glUniform3fv(
					glGetUniformLocation(shader->program, "material.ambient"),
					1,
					(GLfloat *)&ambient);
			glUniform3fv(
					glGetUniformLocation(shader->program, "material.diffuse"),
					1,
					(GLfloat *)&diffuse);
			glUniform3fv(
					glGetUniformLocation(shader->program, "material.specular"),
					1,
					(GLfloat *)&specular);
			glUniform1f(
					glGetUniformLocation(shader->program, "material.shininess"),
					shininess);
			glBindVertexArray(m_mesh->mesh[i]->VAO);
			glDrawElements(GL_TRIANGLES, m_mesh->mesh[i]->nb_indices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			i++;
		}
		glUseProgram(0);
	}

}

bool		scene_shader_add(t_scene *scene,
						const char *vertex_shader_path,
						const char *fragment_shader_path)
{
	scene->m_shader->add(scene->m_shader, vertex_shader_path, fragment_shader_path);
	return (true);
}

bool		scene_mesh_add(t_scene *scene, t_mesh *mesh)
{
	scene->m_mesh->add(scene->m_mesh, mesh);
	return (true);
}

bool		scene_model_add(t_scene *scene, t_model *model)
{
	scene->m_model->add(scene->m_model, model);
	return (true);
}


t_scene		*scene_construct()
{
	t_scene *scene;

	if (!(scene = ft_memalloc(sizeof(t_scene))))
		return (NULL);
	scene->shader_add = &scene_shader_add;
	scene->model_add = &scene_model_add;
	scene->mesh_add = &scene_mesh_add;
	if (!(scene->m_model = m_model_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_mesh = m_mesh_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_shader = m_shader_construct()))
		return (scene_destruct(&scene));
	if (!(scene->cam = cam_construct()))
		return (scene_destruct(&scene));
	return (scene);
}

void		*scene_destruct(t_scene **scene)
{
	if (scene && *scene)
	{
		if ((*scene)->m_mesh)
			m_mesh_destruct(&(*scene)->m_mesh);
		if ((*scene)->m_model)
			m_model_destruct(&(*scene)->m_model);
		if ((*scene)->m_shader)
			m_shader_destruct(&(*scene)->m_shader);
		if ((*scene)->cam)
			cam_destruct(&(*scene)->cam);
		ft_memdel((void **)scene);
	}
	return (NULL);
}
