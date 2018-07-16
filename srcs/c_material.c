#include "scop.h"

t_material		*material_construct()
{
	t_material *material;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	return (material);
}

void		*material_destruct(t_material **material)
{
	if (material && *material)
		ft_memdel((void **)material);
	return (NULL);
}

bool			m_material_add(t_m_material *m_material, t_material *material)
{
	if (!(m_material->material = realloc(m_material->material, sizeof(t_material **) * (m_material->size + 1))))
	{
		m_material->size = 0;
		return (false);
	}
	m_material->material[m_material->size] = material;
	m_material->size++;
	return (true);
}

t_material			*m_material_new(t_m_material *m_material)
{
	t_material *new;

	if (!(new = material_construct()))
		return (NULL);
	if (!(m_material->material = realloc(m_material->material, sizeof(t_material **) * (m_material->size + 1))))
	{
		m_material->size = 0;
		return (false);
	}
	m_material->material[m_material->size] = new;
	m_material->size++;
	return (new);
}

t_m_material		*m_material_construct()
{
	t_m_material *m_material;

	if (!(m_material = ft_memalloc(sizeof(t_m_material))))
		return (NULL);
	m_material->add = &m_material_add;
	m_material->new = &m_material_new;
	return (m_material);
}

void		*m_material_destruct(t_m_material **m_material)
{
	unsigned int i;

	if (m_material && *m_material)
	{
		if ((*m_material)->size)
		{
			i = 0;
			while (i < (*m_material)->size)
			{
				material_destruct(&(*m_material)->material[i]);
				i++;
			}
			ft_memdel((void **)&(*m_material)->material);
		}
		ft_memdel((void **)m_material);
	}
	return (NULL);
}
