/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_model_parse_get_index.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:56:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:59:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			m_model_json_parse_shader(cJSON *get,
											const char *key,
											t_scene *scene,
											t_model *model)
{
	cJSON *source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!source)
		return (false);
	if (cJSON_IsNumber(source))
	{
		model->index_shader = source->valueint;
		return (true);
	}
	else if (cJSON_IsString(source) && source->valuestring)
	{
		model->index_shader = m_shader_get_index(scene->m_shader,
			source->valuestring);
		return (true);
	}
	return (false);
}

bool			m_model_json_parse_material(cJSON *get,
											const char *key,
											t_scene *scene,
											t_model *model)
{
	cJSON *source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!source)
		return (false);
	if (cJSON_IsNumber(source))
	{
		model->index_material = source->valueint;
		return (true);
	}
	else if (cJSON_IsString(source) && source->valuestring)
	{
		model->index_material = m_material_get_index(scene->m_material,
			source->valuestring);
		return (true);
	}
	return (false);
}
