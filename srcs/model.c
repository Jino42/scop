
#include "scop.h"

/*
** System de flag inter mesh si uniform changê
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
bool		push_mesh(t_model *model, t_mesh *new_mesh)
{
	model->size_mesh++;
	model->mesh = realloc(model->mesh, model->size_mesh * sizeof(t_mesh *));
	model->mesh[model->size_mesh - 1] = new_mesh;
}

bool		model_loader(t_model *model,
						const char *name_obj,
						const char *path_obj)
{
	int fd;
	char *full_path_obj = ft_strjoin(name_obj, path_obj);
	t_mesh *mesh;

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (false);
	if (!(mesh = ft_memalloc(t_mesh)))
		return (NULL);
	;
	return (true);
}
*/

void		model_render(t_model *model, t_cam *cam, t_light *light,
								t_matrix *view, t_matrix *projection,
								t_shader *shader, t_material *material)
{
	t_m_meshs *meshs;
	t_matrix temp, mvp;

	meshs = model->meshs;

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
	glUniform3f(
			glGetUniformLocation(shader->program, "cameraPosition"),
			cam->position.x,
			cam->position.y,
			cam->position.z);
	glUniformMatrix4fv(
			glGetUniformLocation(shader->program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);
	glUniformMatrix4fv(
			glGetUniformLocation(shader->program, "M"),
			1, GL_FALSE, &model->transform.matrix[0][0]);
	uint32_t i = 0;
	while (i < meshs->size)
	{
		if (model->flag & F_TEXTURE)
		{
			glUniform1i(glGetUniformLocation(shader->program, "testTexture"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model->textures->texture[i]->id);
		}
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
