
#include "scop.h"

/*
** System de flag inter mesh si uniform changê
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_m_meshs		*construct_m_meshs()
{
	t_m_meshs *meshs;

	if (!(meshs = ft_memalloc(sizeof(t_m_meshs))))
		return (NULL);
	return (meshs);
}

void		model_render(t_model *model, t_cam *cam, t_light *light,
								t_matrix *view, t_matrix *projection,
								t_shader *shader)
{
	t_m_meshs *meshs;
	t_matrix temp, mvp;

	meshs = model->meshs;
	t_material *material = NULL;

	shader->use(shader);
	temp = matrix_get_mult_matrix(&model->transform, view);
	mvp = matrix_get_mult_matrix(&temp, projection);
	glUniform3fv(
			glGetUniformLocation(shader->program, "light.ambient"),
			1,
			(GLfloat *)&light->ambient);
	glUniform3fv(
			glGetUniformLocation(shader->program, "light.diffuse"),
			1,
			(GLfloat *)&light->diffuse);
	glUniform3fv(
			glGetUniformLocation(shader->program, "light.specular"),
			1,
			(GLfloat *)&light->specular);
	glUniform3fv(
			glGetUniformLocation(shader->program, "light.position"),
			1,
			(GLfloat *)&light->position);
	glUniform3f(
			glGetUniformLocation(shader->program, "cameraPosition"),
			cam->position.x,
			cam->position.y,
			cam->position.z);
	glUniform3f(
			glGetUniformLocation(shader->program, "camDir"),
			cam->to.x,
			cam->to.y,
			cam->to.z);
	glUniformMatrix4fv(
			glGetUniformLocation(shader->program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);
	glUniformMatrix4fv(
			glGetUniformLocation(shader->program, "V"),
			1, GL_FALSE, &view->matrix[0][0]);
	glUniformMatrix4fv(
			glGetUniformLocation(shader->program, "P"),
			1, GL_FALSE, &projection->matrix[0][0]);
	glUniformMatrix4fv(
			glGetUniformLocation(shader->program, "M"),
			1, GL_FALSE, &model->transform.matrix[0][0]);
	uint32_t i = 0;
	while (i < meshs->size)
	{
		if (model->flag & F_TEXTURE)
		{
			material =  meshs->mesh[i]->material;
			glUniform1i(glGetUniformLocation(shader->program, "testTexture"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, material->texture_diffuse);
		}
		else
			material = model->materials->material[0];
		glUniform3fv(
				glGetUniformLocation(shader->program, "material.ambient"),
				1,
				(GLfloat *)&material->ambient);
		glUniform3fv(
				glGetUniformLocation(shader->program, "material.diffuse"),
				1,
				(GLfloat *)&material->diffuse);
		glUniform3fv(
				glGetUniformLocation(shader->program, "material.specular"),
				1,
				(GLfloat *)&material->specular);
		glUniform1f(
				glGetUniformLocation(shader->program, "material.shininess"),
				material->shininess);
		glBindVertexArray(meshs->mesh[i]->VAO);
		glDrawElements(GL_TRIANGLES, meshs->mesh[i]->nb_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		i++;
	}
	glUseProgram(0);
}

void	*model_destroy(t_model **model)
{
	if (!model || !*model)
		return (NULL);
	ft_memdel((void *)model);
	return (NULL);
}

t_model	*model_construct(const char *path,
						const char *path_obj,
						const char *path_texture)
{
	t_model		*model;

	(void)path_texture;
	if (!(model = ft_memalloc(sizeof(t_model))))
		return (NULL);
	printf("Path : %s\n", path);
	model->path = (unsigned char *)strdup(path);
	model->textures = textures_construct();
	model->materials = materials_construct();
	model->meshs = construct_m_meshs();
	model->transform = matrix_get_identity();
	obj_pars(model, path_obj); // Hyper instable
	model->type_draw = GL_POINTS;
	if (path_texture)
	{
		model->flag |= F_TEXTURE;
		model->textures->add(model->textures, path_texture);
	}
	//model->render = &model_render;
	return (model);
}
