/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 21:46:41 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/02/01 21:48:28 by ntoniolo         ###   ########.fr       */
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

t_material			*material_construct_tab()
{
	t_material	*material;

	if (!(material = ft_memalloc(sizeof(t_material) * NB_MAT)))
		return (NULL);
	MAT_EMERALD((&material[F_MAT_EMERALD]));
	MAT_PR((&material[F_MAT_PR]));
//	material[F_MAT_PEARL] = MAT_PEARL;
//	material[F_MAT_JADE] = MAT_JADE;
//	material[F_MAT_RED_PLASTIC] = MAT_RED_PLASTIC;
	return (material);
}

t_material		*material_construct()
{
	t_material *material;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	material->set_map = &material_set_map;
	MAT_PR(material);
	return (material);
}

void			*material_destruct(t_material **material)
{
	ft_memdel((void *)material);
	return (NULL);
}

t_m_materials	*materials_construct()
{
	t_m_materials *materials;

	if (!(materials = ft_memalloc(sizeof(t_m_materials))))
		return (NULL);
	return (materials);
}
