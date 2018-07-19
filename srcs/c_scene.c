#include "scop.h"

void		scene_render(t_scene *scene)
{
	t_material *material;
	t_light *light;
	light = scene->m_light->light[scene->index_light];

	t_m_mesh *m_mesh;
	t_model	*model;
	t_shader	*shader;
	t_matrix temp, mvp;

	for (unsigned int i = 0; i < scene->m_model->size; i++)
	{
		model = scene->m_model->model[i];
		shader = scene->m_shader->shader[model->index_shader];
		material = scene->m_material->material[model->index_material];
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
						const char *fragment_shader_path,
						const char *name)
{
	scene->m_shader->add(scene->m_shader, vertex_shader_path, fragment_shader_path, name);
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

bool		scene_parse(t_scene *scene, const char *path)
{
	char			buffer[MAX_SOURCE_SIZE];
	cJSON			*json;

	bzero(buffer, MAX_SOURCE_SIZE);
	if (!(json = json_load_src(path, buffer)))
		return (false);
	if (!(m_material_json_parse(scene->m_material, json, "material")))
	{
		cJSON_Delete(json);
		return (false);
	}
	if (!(m_light_json_parse(scene->m_light, json, "light")))
	{
		cJSON_Delete(json);
		return (false);
	}
	if (!(m_shader_json_parse(scene->m_shader, json, "shader")))
	{
		cJSON_Delete(json);
		return (false);
	}
	if (!(m_model_json_parse(scene, json, "model")))
	{
		cJSON_Delete(json);
		return (false);
	}
	cJSON_Delete(json);
	return (true);
}

t_scene		*scene_construct(const char *path)
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
	if (!(scene->m_material = m_material_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_light = m_light_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_texture = m_texture_construct()))
		return (scene_destruct(&scene));
	if (!(scene->cam = cam_construct()))
		return (scene_destruct(&scene));
	if (!(scene_parse(scene, path)))
		return (scene_destruct(&scene));
	if (!scene_require(scene))
		return (scene_destruct(&scene));
	return (scene);
}

void		*scene_destruct(t_scene **scene)
{
	if (scene && *scene)
	{
		if ((*scene)->m_model)
			m_model_destruct(&(*scene)->m_model);
		if ((*scene)->m_mesh)
			m_mesh_destruct(&(*scene)->m_mesh);
		if ((*scene)->m_shader)
			m_shader_destruct(&(*scene)->m_shader);
		if ((*scene)->m_material)
			m_material_destruct(&(*scene)->m_material);
		if ((*scene)->m_light)
			m_light_destruct(&(*scene)->m_light);
		if ((*scene)->cam)
			cam_destruct(&(*scene)->cam);
		if ((*scene)->m_texture)
			m_texture_destruct(&(*scene)->m_texture);
		ft_memdel((void **)scene);
	}
	return (NULL);
}

bool		scene_reload(t_scene **scene, const char *path)
{
	scene_destruct(scene);
	if (!((*scene) = scene_construct(path)))
		return (false);
	if (!scene || !(*scene))
		return (false);
	return (true);
}


bool		scene_require_index_m_model(t_scene *scene)
{
	t_model *model;
	unsigned int i;

	i = 0;
	while (i < scene->m_model->size)
	{
		model = scene->m_model->model[i];
		if (model->index_shader >= scene->m_model->size)
			return (dprintf(2, "Votre model %s doit avoir un index ou un nom de shader valide.\n", model->name) && 0);
		if (model->index_material >= scene->m_material->size)
			return (dprintf(2, "Votre model %s doit avoir un index ou un nom de materiaux valide.\n", model->name) && 0);
		i++;
	}
	return (true);
}

bool		scene_require(t_scene *scene)
{
	if (!scene->m_model->size)
		return (ft_bool_error("La Scene a besoin d'au moins d'un Model", NULL, NULL));
	if (!scene->m_shader->size)
		return (ft_bool_error("La Scene a besoin d'au moins d'un Shader", NULL, NULL));
	if (!scene->m_material->size)
		return (ft_bool_error("La Scene a besoin d'au moins d'un Materiau", NULL, NULL));
	if (!scene_require_index_m_model(scene))
		return (false);
	return (true);
}



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool		scene_write(t_scene *scene, const char *path)
{
	cJSON	*json_scene;
	char	*str;
	int		fd;

	if ((fd = open(path, O_RDWR|O_CREAT, 0666)) <= 0)
		return (false);
	printf("%i\n", fd);
	if (!(json_scene = cJSON_CreateObject()))
	{
		close(fd);
		return (false);
	}
	if (!m_model_json_write(scene->m_model, json_scene) ||
		!m_shader_json_write(scene->m_shader, json_scene) ||
		!m_light_json_write(scene->m_light, json_scene) ||
		!m_material_json_write(scene->m_material, json_scene))
	{
		close(fd);
		cJSON_Delete(json_scene);
		return (false);
	}
	str = cJSON_Print(json_scene);
	dprintf(fd, "%s\n", str);
	close(fd);
	free(str);
	cJSON_Delete(json_scene);
	return (true);
}
