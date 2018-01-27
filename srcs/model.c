
#include "scop.h"

/*
** System de flag inter mesh si uniform changê
*/

void		model_render(t_model *model, t_cam *cam, t_light *light,
								t_matrix *view, t_matrix *projection)
{
	t_mesh *mesh;
	t_matrix temp, mvp;

	mesh = model->mesh;
	mesh->shader->use(mesh->shader);
	temp = matrix_get_mult_matrix(&model->transform, view);
	mvp = matrix_get_mult_matrix(&temp, projection);
	glUniform3fv(
			glGetUniformLocation(mesh->shader->program, "light.ambient"),
			1,
			(GLfloat *)&light->ambient);
	glUniform3fv(
			glGetUniformLocation(mesh->shader->program, "light.diffuse"),
			1,
			(GLfloat *)&light->diffuse);
	glUniform3fv(
			glGetUniformLocation(mesh->shader->program, "light.specular"),
			1,
			(GLfloat *)&light->specular);
	glUniform3fv(
			glGetUniformLocation(mesh->shader->program, "light.position"),
			1,
			(GLfloat *)&light->position);
	glUniform3fv(
			glGetUniformLocation(mesh->shader->program, "material.ambient"),
			1,
			(GLfloat *)&mesh->material->ambient);
	glUniform3fv(
			glGetUniformLocation(mesh->shader->program, "material.diffuse"),
			1,
			(GLfloat *)&mesh->material->diffuse);
	glUniform3fv(
			glGetUniformLocation(mesh->shader->program, "material.specular"),
			1,
			(GLfloat *)&mesh->material->specular);
	glUniform1f(
			glGetUniformLocation(mesh->shader->program, "material.shininess"),
			mesh->material->shininess);
	glUniform3f(
			glGetUniformLocation(mesh->shader->program, "cameraPosition"),
			cam->position.x,
			cam->position.y,
			cam->position.z);
	glUniformMatrix4fv(
			glGetUniformLocation(mesh->shader->program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);
	glUniformMatrix4fv(
			glGetUniformLocation(mesh->shader->program, "M"),
			1, GL_FALSE, &model->transform.matrix[0][0]);
	glBindVertexArray(mesh->VAO);
	glDrawElements(GL_TRIANGLES, mesh->nb_indices, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}



void	*model_destroy(t_model **model)
{
	if (!model || !*model)
		return (NULL);
	ft_memdel((void *)model);
	return (NULL);
}

t_model	*model_construct(t_mesh *mesh)
{
	t_model		*model;

	if (!(model = ft_memalloc(sizeof(t_model))))
		return (model_destroy(&model));
	model->mesh = mesh;
	model->transform = matrix_get_identity();
	model->render = &model_render;
	return (model);
}
