/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:12:14 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/19 21:01:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool				material_set_map(t_material *material,
										uint32_t flag,
										const GLuint map_id)
{
	material->flag |= flag;
	if (flag & MATERIAL_MAP_SHININESS)
		material->texture_shininess = map_id;
	if (flag & MATERIAL_MAP_NORMAL)
		material->texture_normal = map_id;
	if (flag & MATERIAL_MAP_SPECULAR)
		material->texture_specular = map_id;
	if (flag & MATERIAL_MAP_DIFFUSE)
		material->texture_diffuse = map_id;
	if (flag & MATERIAL_MAP_AMBIENT)
		material->texture_ambient = map_id;
	return (true);
}

bool				material_set_texture(t_material *material, const t_texture *texture)
{
	material->flag |= texture->flag;
	if (material->flag & MATERIAL_MAP_SHININESS)
		material->texture_shininess = texture->id;
	if (material->flag & MATERIAL_MAP_NORMAL)
		material->texture_normal = texture->id;
	if (material->flag & MATERIAL_MAP_SPECULAR)
		material->texture_specular = texture->id;
	if (material->flag & MATERIAL_MAP_DIFFUSE)
		material->texture_diffuse = texture->id;
	if (material->flag & MATERIAL_MAP_AMBIENT)
		material->texture_ambient = texture->id;
	return (true);
}

t_material		*material_construct(char *name, const int material_type)
{
	t_material *material;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	if (material_type == MATERIAL_MTLLIB)
		material->flag |= MATERIAL_MTLLIB;
	material->name = strdup(name);
	return (material);
}

void			*material_destruct(t_material **material)
{
	if (material && *material)
	{
		ft_memdel((void **)(&(*material)->name));
		ft_memdel((void **)material);
	}
	return (NULL);
}
