#include "scop.h"

t_model		*model_construct()
{
	t_model *model;

	if (!(model = ft_memalloc(sizeof(t_model))))
		return (NULL);
	return (model);
}

void		*model_destruct(t_model **model)
{
	if (model && *model)
		ft_memdel((void **)model);
	return (NULL);
}

bool			m_model_add(t_m_model *m_model)
{
	t_model *model;

	if (!(model = model_construct()))
		return (false);
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
