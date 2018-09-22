/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:06:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/22 19:12:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mesh		*mesh_construct(void)
{
	t_mesh *mesh;

	if (!(mesh = ft_memalloc(sizeof(t_mesh))))
		return (NULL);
	mesh->indexed_v = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_vt = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_vn = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_color = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_u = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indices = ft_memalloc(sizeof(GLuint) * BUFFER_OBJ);
	return (mesh);
}

void		*mesh_destruct(t_mesh **mesh)
{
	if (mesh && *mesh)
	{
		if ((*mesh)->indexed_v)
			ft_memdel((void **)&((*mesh)->indexed_v));
		if ((*mesh)->indexed_vt)
			ft_memdel((void **)&((*mesh)->indexed_vt));
		if ((*mesh)->indexed_vn)
			ft_memdel((void **)&((*mesh)->indexed_vn));
		if ((*mesh)->indexed_color)
			ft_memdel((void **)&((*mesh)->indexed_color));
		if ((*mesh)->indexed_u)
			ft_memdel((void **)&((*mesh)->indexed_u));
		if ((*mesh)->indices)
			ft_memdel((void **)&((*mesh)->indices));
		ft_memdel((void **)mesh);
	}
	return (NULL);
}
