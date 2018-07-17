/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:46:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:47:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_model		*model_construct(const char *path, const char *name)
{
	t_model		*model;

	printf("%s %s\n", path, name);
	if (!(model = ft_memalloc(sizeof(t_model))))
		return (NULL);
	model->transform = matrix_get_identity();
	model->type_draw = GL_FILL;
	if (!(model->m_mesh = m_mesh_construct()))
		return (model_destruct(&model));
	model->name = strdup(name);
	model->path = strdup(path);
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
		if ((*model)->name)
			ft_memdel((void **)&(*model)->name);
		if ((*model)->path)
			ft_memdel((void **)&(*model)->path);
		ft_memdel((void **)model);
	}
	return (NULL);
}
