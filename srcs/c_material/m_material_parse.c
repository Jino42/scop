/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_material_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:12:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/23 16:01:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		m_material_json_loop_parse_2(t_material *material,
											cJSON *json_material,
											int index)
{
	if (!json_parse_vector(json_material, "ambient", &material->ambient))
	{
		return (dprintf(2, "JSON material[%i] %s : ambient error\n",
				index, material->name) == 0);
	}
	if (!json_parse_vector(json_material, "diffuse", &material->diffuse))
	{
		return (dprintf(2, "JSON material[%i] %s : diffuse error\n",
				index, material->name) == 0);
	}
	if (!json_parse_vector(json_material, "specular", &material->specular))
	{
		return (dprintf(2, "JSON material[%i] %s : specular error\n",
				index, material->name) == 0);
	}
	if (!json_parse_float(json_material, "shininess", &material->shininess))
	{
		return (dprintf(2, "JSON material[%i] %s : shininess error\n",
				index, material->name) == 0);
	}
	return (true);
}

static bool		m_material_json_loop_parse(t_m_texture *m_texture,
											t_m_material *m_material,
											cJSON *json_material,
											int index)
{
	char			*str;
	t_material		*material;
	t_texture		*texture;

	str = NULL;
	if (!json_parse_string(json_material, "name", &str))
	{
		return (dprintf(2, "JSON material[%i]: the name is Undefined\n",
				index) == 0);
	}
	if (!(material = m_material->new(m_material, str, 0)))
		return (false);
	if (!m_material_json_loop_parse_2(material, json_material, index))
		return (false);
	if (json_parse_string(json_material, "Kd", &str))
	{
		if (!(texture = m_texture->new(m_texture,
			MATERIAL_MAP_DIFFUSE, str)))
			return (false);
		material_set_texture(material, texture);
		printf("Ok\n");
	}
	return (true);
}

static bool		m_material_json_loop(t_m_texture *m_texture,
									t_m_material *m_material,
										cJSON *json_materials)
{
	int				index;
	cJSON			*json_material;

	if (!json_materials)
		return (ft_bool_error("JSON materials is undefined ", NULL, NULL));
	json_material = json_materials->child;
	index = 0;
	while (json_material)
	{
		if (!m_material_json_loop_parse(m_texture, m_material, json_material, index))
			return (false);
		json_material = json_material->next;
		index++;
	}
	return (true);
}

bool			m_material_json_parse(t_m_texture *m_texture,
										t_m_material *m_material,
										cJSON *get,
										const char *key)
{
	cJSON	*source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!(m_material_json_loop(m_texture, m_material, source)))
	{
		return (ft_bool_error("Erreur: Le parsing de t_m_material a échoué",
				NULL, NULL));
	}
	return (true);
}
