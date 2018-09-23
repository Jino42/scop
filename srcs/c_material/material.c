/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:12:14 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/23 23:57:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool				material_set_map(t_material *material,
										uint32_t flag,
										const GLuint map_id)
{
	material->flag |= flag;
	if (flag & MATERIAL_MAP_DIFFUSE)
		material->texture_diffuse = map_id;
	return (true);
}

bool				material_set_texture(t_material *material,
											const t_texture *texture)
{
	material->flag |= texture->flag;
	if (material->flag & MATERIAL_MAP_DIFFUSE)
	{
		material->texture_diffuse = texture->id;
		material->texture = texture;
	}
	return (true);
}

bool				material_unset_texture(t_material *material,
											const t_texture *texture)
{
	if (material->flag & MATERIAL_MAP_DIFFUSE)
	{
		material->texture_diffuse = texture->id;
		material->flag ^= MATERIAL_MAP_DIFFUSE;
	}
	return (true);
}

t_material			*material_construct(char *name, const int material_type)
{
	t_material *material;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	if (material_type == MATERIAL_MTLLIB)
		material->flag |= MATERIAL_MTLLIB;
	material->name = strdup(name);
	return (material);
}

void				*material_destruct(t_material **material)
{
	if (material && *material)
	{
		ft_memdel((void **)(&(*material)->name));
		ft_memdel((void **)material);
	}
	return (NULL);
}
