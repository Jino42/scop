#include "scop.h"

bool			m_model_json_parse_shader(cJSON *get, const char *key, t_scene *scene, t_model *model)
{
	cJSON *source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!source)
		return (false);
	if (cJSON_IsNumber(source))
	{
		model->index_shader = source->valueint;
		return (true);
	}
	else if (cJSON_IsString(source) && source->valuestring)
	{
		model->index_shader = m_shader_get_index(scene->m_shader, source->valuestring);
		return (true);
	}
	return (false);
}

bool			m_model_json_parse_material(cJSON *get, const char *key, t_scene *scene, t_model *model)
{
	cJSON *source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!source)
		return (false);
	if (cJSON_IsNumber(source))
	{
		model->index_material = source->valueint;
		return (true);
	}
	else if (cJSON_IsString(source) && source->valuestring)
	{
		model->index_material = m_material_get_index(scene->m_material, source->valuestring);
		return (true);
	}
	return (false);
}

bool			m_model_json_loop(t_scene *scene, t_m_model *m_model, cJSON *json_models)
{
	int				index;
	char			*str[2];
	cJSON			*json_model;
	t_model			*model;
	t_vector		tmp;

	if (!json_models)
		return (ft_bool_error("JSON models is undefined ", NULL, NULL));
	json_model = json_models->child;
	index = 0;
	while (json_model)
	{
		bzero(str, sizeof(char *) * 2);
		if (!json_parse_string(json_model, "path", &str[0]))
			return (dprintf(2, "JSON model[%i]: the path is Undefined\n", index) == 0);
		if (!json_parse_string(json_model, "name", &str[1]))
			return (dprintf(2, "JSON model[%i]: the name is Undefined\n", index) == 0);
		if (!(model = m_model_load(m_model, str[0], str[1])))
			return (dprintf(2, "JSON model[%i]: Load model Failed\n", index) == 0);
		if (!json_parse_vector(json_model, "position", &model->position))
			return (dprintf(2, "JSON model[%i] %s : position error\n", index, model->name) == 0);
		if (json_parse_vector(json_model, "scaling", &tmp))
		{
			model->scaling = tmp;
			model->same_scaling = tmp.x;
		}
		if (!json_parse_vector(json_model, "rotation", &model->rotation))
			return (dprintf(2, "JSON model[%i] %s : rotation error\n", index, model->name) == 0);
		if (!(m_model_json_parse_shader(json_model, "shader", scene, model)))
			return (dprintf(2, "JSON model[%i] %s : shader error\n", index, model->name) == 0);
		if (!(m_model_json_parse_material(json_model, "material", scene, model)))
			return (dprintf(2, "JSON model[%i] %s : shader error\n", index, model->name) == 0);
		json_model = json_model->next;
		index++;
	}
	return (true);
}

bool			m_model_json_parse(t_scene *scene, t_m_model *m_model, cJSON *get, const char *key)
{
	cJSON	*source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!(m_model_json_loop(scene, m_model, source)))
		return (ft_bool_error("Erreur: Le parsing de t_m_model a échoué", NULL, NULL));
	return (true);
}

t_model		*model_construct(const char *path, const char *name)
{
	t_model		*model;

	if (!(model = ft_memalloc(sizeof(t_model))))
		return (NULL);
	model->transform = matrix_get_identity();
	model->type_draw = GL_FILL;
	if (!(model->m_mesh = m_mesh_construct()))
		return (model_destruct(&model));
	model->name = strdup(name);
	model->path = strdup(path);
	model->scaling = vector_construct(1.f, 1.f, 1.f);
	model->update = true;
	model->same_scaling = 1;
	return (model);
}

void		*model_destruct(t_model **model)
{
	if (model && *model)
	{
		if ((*model)->m_mesh)
			m_mesh_destruct(&(*model)->m_mesh);
		if ((*model)->name)
			ft_memdel((void **)&(*model)->name);
		ft_memdel((void **)model);
	}
	return (NULL);
}

bool			m_model_add(t_m_model *m_model, t_model *model)
{
	if (!(m_model->model = realloc(m_model->model, sizeof(t_model **) * (m_model->size + 1))))
	{
		m_model->size = 0;
		return (false);
	}
	if (!(m_model->model_name = realloc(m_model->model_name, sizeof(char **) * (m_model->size + 1))))
	{
		m_model->size = 0;
		return (false);
	}
	m_model->model[m_model->size] = model;
	m_model->model_name[m_model->size] = model->name;
	m_model->size++;
	return (true);
}

t_model			*m_model_new(t_m_model *m_model, char *path, char *name)
{
	t_model *model;

	if (!(model = model_construct(path, name)))
		return (NULL);
	if (!(m_model->model = realloc(m_model->model, sizeof(t_model **) * (m_model->size + 1))))
	{
		m_model->size = 0;
		return (false);
	}
	if (!(m_model->model_name = realloc(m_model->model_name, sizeof(char **) * (m_model->size + 1))))
	{
		m_model->size = 0;
		return (false);
	}
	m_model->model[m_model->size] = model;
	m_model->model_name[m_model->size] = model->name;
	m_model->size++;
	return (model);
}

t_m_model		*m_model_construct()
{
	t_m_model *m_model;

	if (!(m_model = ft_memalloc(sizeof(t_m_model))))
		return (NULL);
	m_model->add = &m_model_add;
	m_model->new = &m_model_new;
	return (m_model);
}

void		*m_model_destruct(t_m_model **m_model)
{
	unsigned int i;

	if (m_model && *m_model)
	{
		if ((*m_model)->size)
		{
			i = 0;
			while (i < (*m_model)->size)
			{
				model_destruct(&(*m_model)->model[i]);
				i++;
			}
			ft_memdel((void **)&(*m_model)->model);
			ft_memdel((void **)&(*m_model)->model_name);
		}
		ft_memdel((void **)m_model);
	}
	return (NULL);
}

void		model_gen_gl_buffers(t_model *model)
{
	unsigned int	i;

	i = 0;
	while (i < model->m_mesh->size)
	{
		mesh_gen_gl_buffers(model->m_mesh->mesh[i]);
		i++;
	}
}

void	model_setup_scaling(t_model *model)
{
	t_vector	diff;
	float		scaling;

	diff = vector_get_sub(&model->min, &model->max);
	diff = vector_get_abs(&diff);
	if (diff.x > diff.y && diff.x > diff.z)
		scaling = 1.f / diff.x;
	else if (diff.y > diff.x && diff.y > diff.z)
		scaling = 1.f / diff.y;
	else
		scaling = 1.f / diff.z;
	//model->scaling = vector_construct(scaling, scaling, scaling);
	model->inter_scaling = scaling;
	//model->same_scaling = scaling;
	diff = vector_construct(0.f, -0.5f, 0.f);
	vector_add(&model->position, &diff);
	model->center = diff;
	model->negative_center = vector_get_invert(&diff);
	model_compute_transform(model);
}

void	model_compute_transform(t_model *model)
{
	t_vector	scaling;
	float		same_scaling;

	matrix_identity(&model->transform);
	if (model->flag & MODEL_SAME_SCALING)
	{
		same_scaling = model->inter_scaling * model->same_scaling;
		matrix_scaling(&model->transform, same_scaling);
	}
	else
	{
		scaling = vector_get_mult(&model->scaling, model->inter_scaling);
		matrix_vector_scaling(&model->transform, &scaling);
	}
	matrixgl_rotation_x(&model->transform, model->rotation.x);
	matrixgl_rotation_y(&model->transform, model->rotation.y);
	matrixgl_rotation_z(&model->transform, model->rotation.z);
	matrixgl_translation(&model->transform, &model->position);
}
void	model_update(t_model *model)
{
	model->update = false;
	model_compute_transform(model);
}
