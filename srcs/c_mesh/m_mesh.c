/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mesh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:06:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 17:09:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			m_mesh_add(t_m_mesh *m_mesh, t_mesh *mesh)
{
	if (!(m_mesh->mesh = realloc(m_mesh->mesh,
				sizeof(t_mesh **) * (m_mesh->size + 1))))
	{
		m_mesh->size = 0;
		return (false);
	}
	m_mesh->mesh[m_mesh->size] = mesh;
	m_mesh->size++;
	return (true);
}

t_mesh			*m_mesh_new(t_m_mesh *m_mesh)
{
	t_mesh *new;

	if (!(new = mesh_construct()))
		return (NULL);
	if (!(m_mesh->mesh = realloc(m_mesh->mesh,
				sizeof(t_mesh **) * (m_mesh->size + 1))))
	{
		m_mesh->size = 0;
		return (false);
	}
	m_mesh->mesh[m_mesh->size] = new;
	m_mesh->size++;
	return (new);
}

t_m_mesh		*m_mesh_construct(void)
{
	t_m_mesh *m_mesh;

	if (!(m_mesh = ft_memalloc(sizeof(t_m_mesh))))
		return (NULL);
	m_mesh->add = &m_mesh_add;
	m_mesh->new = &m_mesh_new;
	return (m_mesh);
}

void			*m_mesh_destruct(t_m_mesh **m_mesh)
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
