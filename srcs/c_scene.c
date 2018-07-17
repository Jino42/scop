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
	if (!(m_model_json_parse(scene, scene->m_model, json, "model")))
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





bool		m_model_write(t_m_model *m_model, cJSON *json_scene)
{
	cJSON			*json_model;
	cJSON			*json_models;
	t_model			*model;
	unsigned int	i;

	if (!(json_models = cJSON_CreateArray()))
		return (false);
	cJSON_AddItemToObject(json_scene, "model", json_models);

	i = 0;
	while (i < m_model->size)
	{
		model = m_model->model[i];
		if (!(json_model = cJSON_CreateObject()))
			return (false);
		cJSON_AddItemToArray(json_models, json_model);
		if (!json_add_string(json_model, "name", model->name) ||
			!json_add_string(json_model, "path", model->path))
			return (false);
		if (!json_add_int(json_model, "material", model->index_material) ||
			!json_add_int(json_model, "shader", model->index_shader))
			return (false);
		if (!json_add_vector(json_model, "position", &model->position) ||
			!json_add_vector(json_model, "rotation", &model->rotation) ||
			!json_add_vector(json_model, "scaling", &model->scaling))
			return (false);
		i++;
	}
	return (true);
}

bool		m_shader_write(t_m_shader *m_shader, cJSON *json_scene)
{
	cJSON			*json_shader;
	cJSON			*json_shaders;
	t_shader		*shader;
	unsigned int	i;

	if (!(json_shaders = cJSON_CreateArray()))
		return (false);
	cJSON_AddItemToObject(json_scene, "shader", json_shaders);

	i = 0;
	while (i < m_shader->size)
	{
		shader = m_shader->shader[i];
		if (!(json_shader = cJSON_CreateObject()))
			return (false);
		cJSON_AddItemToArray(json_shaders, json_shader);
		if (!json_add_string(json_shader, "name", shader->name) ||
			!json_add_string(json_shader, "vertex", shader->path_vertex) ||
			!json_add_string(json_shader, "fragment", shader->path_fragment))
			return (false);
		i++;
	}
	return (true);
}

bool		m_light_write(t_m_light *m_light, cJSON *json_scene)
{
	cJSON			*json_light;
	cJSON			*json_lights;
	t_light		*light;
	unsigned int	i;

	if (!(json_lights = cJSON_CreateArray()))
		return (false);
	cJSON_AddItemToObject(json_scene, "light", json_lights);

	i = 0;
	while (i < m_light->size)
	{
		light = m_light->light[i];
		if (!(json_light = cJSON_CreateObject()))
			return (false);
		cJSON_AddItemToArray(json_lights, json_light);
		if (!json_add_string(json_light, "name", light->name))
			return (false);
		if (!json_add_vector(json_light, "ambient", &light->ambient) ||
			!json_add_vector(json_light, "diffuse", &light->diffuse) ||
			!json_add_vector(json_light, "specular", &light->specular) ||
			!json_add_vector(json_light, "position", &light->position))
			return (false);
		i++;
	}
	return (true);
}

bool		m_material_write(t_m_material *m_material, cJSON *json_scene)
{
	cJSON			*json_material;
	cJSON			*json_materials;
	t_material		*material;
	unsigned int	i;

	if (!(json_materials = cJSON_CreateArray()))
		return (false);
	cJSON_AddItemToObject(json_scene, "material", json_materials);

	i = 0;
	while (i < m_material->size)
	{
		material = m_material->material[i];
		if (!(json_material = cJSON_CreateObject()))
			return (false);
		cJSON_AddItemToArray(json_materials, json_material);
		if (!json_add_string(json_material, "name", material->name))
			return (false);
		if (!json_add_float(json_material, "shininess", material->shininess))
			return (false);
		if (!json_add_vector(json_material, "ambient", &material->ambient) ||
			!json_add_vector(json_material, "diffuse", &material->diffuse) ||
			!json_add_vector(json_material, "specular", &material->specular))
			return (false);
		i++;
	}
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
	if (!m_model_write(scene->m_model, json_scene) ||
		!m_shader_write(scene->m_shader, json_scene) ||
		!m_light_write(scene->m_light, json_scene) ||
		!m_material_write(scene->m_material, json_scene))
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
