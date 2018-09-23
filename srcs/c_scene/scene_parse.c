/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:34:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/24 00:34:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		scene_parse(t_scene *scene, const char *path)
{
	char			buffer[MAX_SOURCE_SIZE];
	cJSON			*json;

	bzero(buffer, MAX_SOURCE_SIZE);
	if (!(json = json_load_src(path, buffer)))
		return (false);
	(void)scene;
	if (!(m_material_json_parse(scene->m_texture, scene->m_material, json, "material")))
	{
		cJSON_Delete(json);
		return (false);
	}
	if (!(m_light_json_parse(scene->m_light, json, "light")))
	{
		cJSON_Delete(json);
		return (false);
	}
	if (!(m_shader_json_parse(scene->m_shader, json, "shader")))
	{
		cJSON_Delete(json);
		return (false);
	}
	if (!(m_model_json_parse(scene, json, "model")))
	{
		cJSON_Delete(json);
		return (false);
	}
	cJSON_Delete(json);
	return (true);
}
