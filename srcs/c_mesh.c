#include "scop.h"

t_mesh		*mesh_construct()
{
	t_mesh *mesh;

	if (!(mesh = ft_memalloc(sizeof(t_mesh))))
		return (NULL);
	return (mesh);
}

void		*mesh_destruct(t_mesh **mesh)
{
	if (mesh && *mesh)
		ft_memdel((void **)mesh);
	return (NULL);
}

bool			m_mesh_add(t_m_mesh *m_mesh)
{
	t_mesh *mesh;

	if (!(mesh = mesh_construct()))
		return (false);
	if (!(m_mesh->mesh = realloc(m_mesh->mesh, sizeof(t_mesh **) * (m_mesh->size + 1))))
	{
		m_mesh->size = 0;
		return (false);
	}
	m_mesh->mesh[m_mesh->size] = mesh;
	m_mesh->size++;
	return (true);
}

t_m_mesh		*m_mesh_construct()
{
	t_m_mesh *m_mesh;

	if (!(m_mesh = ft_memalloc(sizeof(t_m_mesh))))
		return (NULL);
	m_mesh->add = &m_mesh_add;
	return (m_mesh);
}

void		*m_mesh_destruct(t_m_mesh **m_mesh)
{
	unsigned int i;

	if (m_mesh && *m_mesh)
	{
		if ((*m_mesh)->size)
		{
			i = 0;
			while (i < (*m_mesh)->size)
			{
				mesh_destruct(&(*m_mesh)->mesh[i]);
				i++;
			}
			ft_memdel((void **)&(*m_mesh)->mesh);
		}
		ft_memdel((void **)m_mesh);
	}
	return (NULL);
}
