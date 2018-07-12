#include "scop.h"

t_model		*model_construct(const char *name)
{
	t_model *model;

	if (!(model = ft_memalloc(sizeof(t_model))))
		return (NULL);
	model->transform = matrix_get_identity();
	model->type_draw = GL_FILL;
	if (!(model->m_mesh = m_mesh_construct()))
		return (model_destruct(&model));
	if (!(model->name = strdup(name)))
		return (model_destruct(&model));
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
	for (unsigned int i = 0; i < m_model->size; i++)
	{
		printf("%s\n", m_model->model_name[i]);
	}
	return (true);
}


t_m_model		*m_model_construct()
{
	t_m_model *m_model;

	if (!(m_model = ft_memalloc(sizeof(t_m_model))))
		return (NULL);
	m_model->add = &m_model_add;
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
