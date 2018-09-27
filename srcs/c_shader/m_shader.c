/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:26:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/27 21:25:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			m_shader_add(t_m_shader *m_shader,
								const char *vertex_shader_path,
								const char *fragment_shader_path,
								const char *name)
{
	t_shader *new_shader;

	if (!(new_shader = shader_construct(vertex_shader_path,
				fragment_shader_path, name)))
		return (false);
	if (!(m_shader->shader = realloc(m_shader->shader,
				sizeof(t_shader **) * (m_shader->size + 1))))
	{
		m_shader->size = 0;
		return (false);
	}
	if (!(m_shader->shader_name = realloc(m_shader->shader_name,
				sizeof(char **) * (m_shader->size + 1))))
	{
		m_shader->size = 0;
		return (false);
	}
	m_shader->shader[m_shader->size] = new_shader;
	m_shader->shader_name[m_shader->size] = new_shader->name;
	m_shader->size++;
	return (true);
}

t_m_shader		*m_shader_construct_hidden(void)
{
	t_m_shader *m_shader;

	if (!(m_shader = ft_memalloc(sizeof(t_m_shader))))
		return (NULL);
	m_shader->add = &m_shader_add;
	if (!(m_shader->add(m_shader, "./shader/light.vert",
							"./shader/light.frag", "light")))
		return (m_shader_destruct(&m_shader));
	if (!(m_shader->add(m_shader, "./shader/uv.vert",
							"./shader/cellular.frag", "dynamique texture")))
		return (m_shader_destruct(&m_shader));
	return (m_shader);
}

t_m_shader		*m_shader_construct(void)
{
	t_m_shader *m_shader;

	if (!(m_shader = ft_memalloc(sizeof(t_m_shader))))
		return (NULL);
	m_shader->add = &m_shader_add;
	return (m_shader);
}

void			*m_shader_destruct(t_m_shader **m_shader)
{
	unsigned int i;

	if (m_shader && *m_shader)
	{
		if ((*m_shader)->size)
		{
			i = 0;
			while (i < (*m_shader)->size)
			{
				shader_destruct(&(*m_shader)->shader[i]);
				i++;
			}
			ft_memdel((void **)&(*m_shader)->shader_name);
			ft_memdel((void **)&(*m_shader)->shader);
		}
		ft_memdel((void **)m_shader);
	}
	return (NULL);
}
