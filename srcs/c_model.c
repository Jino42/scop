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
