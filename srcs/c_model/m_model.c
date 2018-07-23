/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_model.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:46:26 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/23 18:49:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			m_model_add(t_m_model *m_model, t_model *model)
{
	if (!(m_model->model = realloc(m_model->model,
				sizeof(t_model **) * (m_model->size + 1))))
	{
		m_model->size = 0;
		return (false);
	}
	if (!(m_model->model_name = realloc(m_model->model_name,
				sizeof(char **) * (m_model->size + 1))))
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
	if (!(m_model->model = realloc(m_model->model,
				sizeof(t_model **) * (m_model->size + 1))))
	{
		m_model->size = 0;
		return (false);
	}
	if (!(m_model->model_name = realloc(m_model->model_name,
				sizeof(char **) * (m_model->size + 1))))
	{
		m_model->size = 0;
		return (false);
	}
	m_model->model[m_model->size] = model;
	m_model->model_name[m_model->size] = model->name;
	m_model->size++;
	return (model);
}

t_m_model		*m_model_construct(void)
{
	t_m_model *m_model;

	if (!(m_model = ft_memalloc(sizeof(t_m_model))))
		return (NULL);
	m_model->add = &m_model_add;
	m_model->new = &m_model_new;
	return (m_model);
}

void			*m_model_destruct(t_m_model **m_model)
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
