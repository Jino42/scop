/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 21:46:41 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/07 23:32:29 by ntoniolo         ###   ########.fr       */
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
//	MAT_EMERALD((&material[F_MAT_EMERALD]));
//	MAT_PR((&material[F_MAT_PR]));
	//material[F_MAT_PEARL] = MAT_PEARL;
	//material[F_MAT_JADE] = MAT_JADE;
	//material[F_MAT_RED_PLASTIC] = MAT_RED_PLASTIC;
	return (material);
}

t_material		*material_construct(const char *name)
{
	t_material *new_material;

	if (!(new_material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	new_material->set_map = &material_set_map;
	if (name)
		new_material->name = strdup(name);
	else
		new_material->name = strdup("no");
	return (new_material);
}

t_material			*materials_find(t_m_materials *materials, const char *name)
{
	uint32_t i;

	i = 0;
	while (i < materials->size)
	{
	//	ft_printf("%s %s\n", materials->material[i]->name, name);
		if (!strcmp(materials->material[i]->name, name))
			return (materials->material[i]);
		i++;
	}
	return (NULL);
}

bool			materials_add(t_m_materials *materials, t_material *material)
{
	if (!(materials->material = realloc(materials->material, sizeof(t_material **) * (materials->size + 1))))
		return (false);
	if (!(materials->material[materials->size] = material))
		return (false);
	materials->size++;
	return (true);
}

void			*material_destruct(t_material **material)
{
	ft_memdel((void *)material);
	return (NULL);
}

t_m_materials		*materials_construct()
{
	t_m_materials	*materials;
	t_material		*material;

	if (!(materials = ft_memalloc(sizeof(t_m_materials))))
		return (NULL);
	material = material_construct("basic");
	MAT_PR(material);
	materials->add = &materials_add;
	materials->search = &materials_find;
	materials->add(materials, material);
	return (materials);
}
