/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:48:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 00:16:18 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			m_light_add(t_m_light *m_light, t_light *light)
{
	if (!(m_light->light = realloc(m_light->light,
				sizeof(t_light **) * (m_light->size + 1))))
	{
		m_light->size = 0;
		return (false);
	}
	if (!(m_light->light_name = realloc(m_light->light_name,
				sizeof(char **) * (m_light->size + 1))))
	{
		m_light->size = 0;
		return (false);
	}
	m_light->light[m_light->size] = light;
	m_light->light_name[m_light->size] = light->name;
	m_light->size++;
	return (true);
}

t_light			*m_light_new(t_m_light *m_light, char *name)
{
	t_light *new;

	if (!(new = light_construct(name)))
		return (NULL);
	if (!(m_light->light = realloc(m_light->light,
				sizeof(t_light **) * (m_light->size + 1))))
	{
		m_light->size = 0;
		return (false);
	}
	if (!(m_light->light_name = realloc(m_light->light_name,
				sizeof(char **) * (m_light->size + 1))))
	{
		m_light->size = 0;
		return (false);
	}
	m_light->light[m_light->size] = new;
	m_light->light_name[m_light->size] = new->name;
	m_light->size++;
	return (new);
}

t_m_light		*m_light_construct(void)
{
	t_m_light *m_light;

	if (!(m_light = ft_memalloc(sizeof(t_m_light))))
		return (NULL);
	m_light->add = &m_light_add;
	m_light->new = &m_light_new;
	return (m_light);
}

void			*m_light_destruct(t_m_light **m_light)
{
	unsigned int i;

	if (m_light && *m_light)
	{
		if ((*m_light)->size)
		{
			i = 0;
			while (i < (*m_light)->size)
			{
				light_destruct(&(*m_light)->light[i]);
				i++;
			}
			ft_memdel((void **)&(*m_light)->light);
			ft_memdel((void **)&(*m_light)->light_name);
		}
		ft_memdel((void **)m_light);
	}
	return (NULL);
}
