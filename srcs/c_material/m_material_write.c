/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_material_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:12:10 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/18 20:00:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		m_material_json_write(t_m_material *m_material, cJSON *json_scene)
{
	cJSON			*json_material;
	cJSON			*json_materials;
	t_material		*material;
	unsigned int	i;

	if (!(json_materials = cJSON_CreateArray()))
		return (false);
	cJSON_AddItemToObject(json_scene, "material", json_materials);
	i = 0;
	while (i < m_material->size)
	{
		material = m_material->material[i];
		if (material->flag & MATERIAL_MTLLIB)
		{
			if (!(json_material = cJSON_CreateObject()))
				return (false);
			cJSON_AddItemToArray(json_materials, json_material);
			if (!json_add_string(json_material, "name", material->name))
				return (false);
			if (!json_add_float(json_material, "shininess", material->shininess)
				|| !json_add_vector(json_material, "ambient", &material->ambient)
				|| !json_add_vector(json_material, "diffuse", &material->diffuse)
				|| !json_add_vector(json_material, "specular", &material->specular))
				return (false);
		}
		i++;
	}
	return (true);
}
