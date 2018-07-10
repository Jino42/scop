#include "scop.h"

t_model		*model_construct()
{
	t_model *model;

	if (!(model = ft_memalloc(sizeof(t_model))))
		return (NULL);
	model->transform = matrix_get_identity();
	model->type_draw = GL_FILL;
	if (!(model->m_mesh = m_mesh_construct()))
		return (model_destruct(&model));
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
	m_model->model[m_model->size] = model;
	m_model->size++;
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
	matrix_scaling(&model->transform, scaling);
	diff = vector_construct(0.f, -0.5f, 0.f);
	matrixgl_translation(&model->transform, &diff);
	model->center = diff;
	model->negative_center = vector_get_invert(&diff);
}
