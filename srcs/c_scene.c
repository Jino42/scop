#include "scop.h"

t_matrix		model_compute_transform_outline(t_model *model)
{
	t_matrix	transform;
	t_vector	scaling;
	float		same_scaling;

	matrix_identity(&transform);
	if (model->flag & MODEL_SAME_SCALING)
	{
		same_scaling = model->inter_scaling * (model->same_scaling * 1.01f);
		matrix_scaling(&transform, same_scaling);
	}
	else
	{
		t_vector sc = model->scaling;
		vector_mult(&model->scaling, 1.1f);
		scaling = vector_get_mult(&model->scaling, model->inter_scaling);
		matrix_vector_scaling(&transform, &scaling);
		model->scaling = sc;
	}
	matrixgl_rotation_x(&transform, model->rotation.x);
	matrixgl_rotation_y(&transform, model->rotation.y);
	matrixgl_rotation_z(&transform, model->rotation.z);
	matrixgl_translation(&transform, &model->position);
	return (transform);
}

void	ftemp(t_scene *scene, t_model *model)
{
	t_matrix temp, mvp;
	t_m_mesh *m_mesh;

	//temp = model_compute_transform_outline(model);
	temp = model->transform;
	temp = matrix_get_mult_matrix(&temp, &scene->cam->view);
	mvp = matrix_get_mult_matrix(&temp, &scene->cam->projection);

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	// /glDisable(GL_DEPTH_TEST);
	shader_use(scene->m_shader_hidden->shader[SHADER_INDEX_OUTLINE]);

	glUniformMatrix4fv(glGetUniformLocation(scene->m_shader_hidden->shader[SHADER_INDEX_OUTLINE]->program, "MVP"), 1, GL_FALSE, &mvp.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(scene->m_shader_hidden->shader[SHADER_INDEX_OUTLINE]->program, "V"), 1, GL_FALSE, &scene->cam->view.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(scene->m_shader_hidden->shader[SHADER_INDEX_OUTLINE]->program, "P"), 1, GL_FALSE, &scene->cam->projection.matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(scene->m_shader_hidden->shader[SHADER_INDEX_OUTLINE]->program, "M"), 1, GL_FALSE, &model->transform.matrix[0][0]);

	m_mesh = model->m_mesh;
	unsigned int i = 0;
	while (i < m_mesh->size)
	{
		glBindVertexArray(m_mesh->mesh[i]->VAO);
		glDrawElements(GL_TRIANGLES, m_mesh->mesh[i]->nb_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		i++;
	}
	glUseProgram(0);
	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
}

void		scene_render(t_scene *scene, float time)
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
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		model = scene->m_model->model[i];
		shader = scene->m_shader->shader[model->index_shader];
		material = scene->m_material->material[model->index_material];
		m_mesh = model->m_mesh;
		glPolygonMode(GL_FRONT_AND_BACK, model->type_draw);

		if (model->update)
			model_update(model);

		shader->use(shader);
		static GLint location[80];
		static int a = 0;
		if (!a)
		{
			location[0] = glGetUniformLocation(shader->program, "light.ambient");
			location[1] = glGetUniformLocation(shader->program, "light.diffuse");
			location[2] = glGetUniformLocation(shader->program, "light.specular");
			location[3] = glGetUniformLocation(shader->program, "light.position");
			location[4] = glGetUniformLocation(shader->program, "light.direction");
			location[5] = glGetUniformLocation(shader->program, "light.constent");
			location[6] = glGetUniformLocation(shader->program, "light.linear");
			location[7] = glGetUniformLocation(shader->program, "light.quadratic");
			location[8] = glGetUniformLocation(shader->program, "light.spot_little_radius");
			location[9] = glGetUniformLocation(shader->program, "light.spot_big_radius");
			location[10] = glGetUniformLocation(shader->program, "light.type");

			location[11] = glGetUniformLocation(shader->program, "cameraPosition");
			location[12] = glGetUniformLocation(shader->program, "camDir");
			location[13] = glGetUniformLocation(shader->program, "MVP");
			location[14] = glGetUniformLocation(shader->program, "V");
			location[15] = glGetUniformLocation(shader->program, "P");
			location[16] = glGetUniformLocation(shader->program, "M");

			location[17] = glGetUniformLocation(shader->program, "testTexture");
			location[18] = glGetUniformLocation(shader->program, "material.texture_diffuse");
			location[19] = glGetUniformLocation(shader->program, "material.texture_specular");
			location[20] = glGetUniformLocation(shader->program, "material.texture_shininess");
			location[21] = glGetUniformLocation(shader->program, "material.texture_normal");
			location[22] = glGetUniformLocation(shader->program, "material.ambient");
			location[23] = glGetUniformLocation(shader->program, "material.diffuse");
			location[24] = glGetUniformLocation(shader->program, "material.specular");
			location[25] = glGetUniformLocation(shader->program, "material.shininess");
			location[26] = glGetUniformLocation(shader->program, "material.flag");
			location[27] = glGetUniformLocation(shader->program, "far");
			location[28] = glGetUniformLocation(shader->program, "near");
			location[29] = glGetUniformLocation(shader->program, "time");
			location[30] = glGetUniformLocation(shader->program, "obj_flag");

			a = 1;
		}


		temp = matrix_get_mult_matrix(&model->transform, &scene->cam->view);
		mvp = matrix_get_mult_matrix(&temp, &scene->cam->projection);

		glUniform1f(location[27], scene->cam->far);
		glUniform1f(location[28], scene->cam->near);
		glUniform1f(location[29], time);


		glUniform3fv(location[0], 1, (GLfloat *)&light->ambient);
		glUniform3fv(location[1], 1, (GLfloat *)&light->diffuse);
		glUniform3fv(location[2], 1, (GLfloat *)&light->specular);
		glUniform3fv(location[3], 1, (GLfloat *)&light->position);
		glUniform3fv(location[4], 1, (GLfloat *)&light->direction);
		glUniform1f(location[5], light->constent);
		glUniform1f(location[6], light->linear);
		glUniform1f(location[7], light->quadratic);
		glUniform1f(location[8], light->spot_little_radius);
		glUniform1f(location[9], light->spot_big_radius);
		glUniform1i(location[10], light->flag & 0xFF);

		glUniform3f(location[11], scene->cam->position.x, scene->cam->position.y, scene->cam->position.z);
		glUniform3f(location[12], scene->cam->to.x, scene->cam->to.y, scene->cam->to.z);
		glUniformMatrix4fv(location[13], 1, GL_FALSE, &mvp.matrix[0][0]);
		glUniformMatrix4fv(location[14], 1, GL_FALSE, &scene->cam->view.matrix[0][0]);
		glUniformMatrix4fv(location[15], 1, GL_FALSE, &scene->cam->projection.matrix[0][0]);
		glUniformMatrix4fv(location[16], 1, GL_FALSE, &model->transform.matrix[0][0]);
		glUniform1i(location[30], model->flag);
		uint32_t i = 0;
		while (i < m_mesh->size)
		{
			if (model->flag & MODEL_USE_DYNAMIQUE_TEXTURE)
			{
				glUniform1i(location[17], 0);
				//glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, scene->rbo->texture_color_buffer);
				glUniform1i(location[18], 1);
			}
			else if (model->flag & MODEL_USE_MATERIAL_PERSONNAL)
			{
				if (scene->m_material_personnal->material[m_mesh->mesh[i]->index_material_personnal]->flag & MATERIAL_MAP_DIFFUSE)
				{
				//	printf("%s %s\n", model->name, scene->m_material_personnal->material[m_mesh->mesh[i]->index_material_personnal]->name);
					glUniform1i(location[17], 0);
					//glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, scene->m_material_personnal->material[m_mesh->mesh[i]->index_material_personnal]->texture_diffuse);
					glUniform1i(location[18], 1);
				}
				else
					glUniform1i(location[18], 0);

				material = scene->m_material_personnal->material[m_mesh->mesh[i]->index_material_personnal];
				/*
				if (!strcmp(model->name, "plant"))
				{
					printf("%s\n", material->name);
					printf("Ka %.2f %.2f %.2f\n", material->ambient.x, material->ambient.y, material->ambient.z);
					printf("Kd %.2f %.2f %.2f\n", material->diffuse.x, material->diffuse.y, material->diffuse.z);
					printf("Ks %.2f %.2f %.2f\n", material->specular.x, material->specular.y, material->specular.z);
					printf(" S %.2f\n", material->shininess);
				}
				*/
			}
			else
			{
				glUniform1i(location[18], 0);
				glUniform1i(location[19], 0);
				glUniform1i(location[20], 0);
				glUniform1i(location[21], 0);
			}
			glUniform3fv(
					location[22],
					1,
					(GLfloat *)&material->ambient);
			glUniform3fv(
					location[23],
					1,
					(GLfloat *)&material->diffuse);
			glUniform3fv(
					location[24],
					1,
					(GLfloat *)&material->specular);
			glUniform1f(
					location[25],
					material->shininess);
			glUniform1f(
					location[26],
					material->flag);
			glBindVertexArray(m_mesh->mesh[i]->VAO);
			glDrawElements(GL_TRIANGLES, m_mesh->mesh[i]->nb_indices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			i++;
		}
		glUseProgram(0);
		//ftemp(scene, model);
	}

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	m_light_render(scene);
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
	if (!(m_texture_json_parse(scene->m_texture_hidden, json, "textures")))
	{
		printf("ABC\n");
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
	if (!(scene->m_model_hidden = m_model_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_model = m_model_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_mesh = m_mesh_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_shader_hidden = m_shader_construct_hidden()))
		return (scene_destruct(&scene));
	if (!(scene->m_shader = m_shader_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_material = m_material_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_material_personnal = m_material_construct()))
		return (scene_destruct(&scene));
	if (!(m_material_add_default(scene->m_material_personnal)))
		return (scene_destruct(&scene));
	if (!(scene->m_light = m_light_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_texture = m_texture_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_texture_hidden = m_texture_construct()))
		return (scene_destruct(&scene));
	if (!(scene->cam = cam_construct()))
		return (scene_destruct(&scene));
	if (!(scene_parse(scene, path)))
		return (scene_destruct(&scene));
	if (!scene_require(scene))
		return (scene_destruct(&scene));
	if (!m_model_hidden_setup(scene))
		return (scene_destruct(&scene));
	if (!(scene->rbo = rbo_construct(WIDTH, HEIGHT)))
		return (scene_destruct(&scene));
	return (scene);
}

void		*scene_destruct(t_scene **scene)
{
	if (scene && *scene)
	{
		if ((*scene)->m_model_hidden)
			m_model_destruct(&(*scene)->m_model_hidden);
		if ((*scene)->m_model)
			m_model_destruct(&(*scene)->m_model);
		if ((*scene)->m_mesh)
			m_mesh_destruct(&(*scene)->m_mesh);
		if ((*scene)->m_shader_hidden)
			m_shader_destruct(&(*scene)->m_shader_hidden);
		if ((*scene)->m_shader)
			m_shader_destruct(&(*scene)->m_shader);
		if ((*scene)->m_material)
			m_material_destruct(&(*scene)->m_material);
		if ((*scene)->m_material_personnal)
			m_material_destruct(&(*scene)->m_material_personnal);
		if ((*scene)->m_light)
			m_light_destruct(&(*scene)->m_light);
		if ((*scene)->cam)
			cam_destruct(&(*scene)->cam);
		if ((*scene)->m_texture)
			m_texture_destruct(&(*scene)->m_texture);
		if ((*scene)->m_texture_hidden)
			m_texture_destruct(&(*scene)->m_texture_hidden);
		if ((*scene)->rbo)
			rbo_destruct(&(*scene)->rbo);
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
