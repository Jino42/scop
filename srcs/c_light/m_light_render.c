#include "scop.h"

bool		m_light_render(t_scene *scene)
{
	t_light		*light;
	t_model		*model;
	t_shader	*shader;
	t_m_mesh	*m_mesh;
	t_matrix	temp;
	t_matrix	mvp;

	for (unsigned int i = 0; i < scene->m_light->size; i++)
	{
		light = scene->m_light->light[i];

		if (light->flag & LIGHT_BASIC)
			model = scene->m_model_hidden->model[MODEL_INDEX_LIGHT_BASIC];
		else if (light->flag & LIGHT_DIRECTIONNAL)
			model = scene->m_model_hidden->model[MODEL_INDEX_LIGHT_DIRECTIONNAL];
		else if (light->flag & LIGHT_POINT)
			model = scene->m_model_hidden->model[MODEL_INDEX_LIGHT_POINT];

		shader = scene->m_shader_hidden->shader[SHADER_INDEX_LIGHT];

		m_mesh = model->m_mesh;
		glPolygonMode(GL_FRONT_AND_BACK, model->type_draw);
		shader->use(shader);


		if (light->update)
			light_compute_transform(light, model);
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
		uint32_t i = 0;
		while (i < m_mesh->size)
		{
			glBindVertexArray(m_mesh->mesh[i]->VAO);
			glDrawElements(GL_TRIANGLES, m_mesh->mesh[i]->nb_indices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			i++;
		}
		glUseProgram(0);
	}

	return (true);
}
