
#include "scop.h"

void		model_render(t_model *model, t_matrix *view, t_matrix *projection)
{
	t_mesh *mesh;
	t_matrix temp, mvp;

	mesh = model->mesh;
	mesh->shader->use(mesh->shader);
	model->transform.matrix[0][0] = 0.005;
	model->transform.matrix[1][1] = 0.005;
	model->transform.matrix[2][2] = 0.005;
	temp = matrix_get_mult_matrix(&model->transform, view);
	mvp = matrix_get_mult_matrix(&temp, projection);
	glUniformMatrix4fv(
			glGetUniformLocation(mesh->shader->program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);

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
