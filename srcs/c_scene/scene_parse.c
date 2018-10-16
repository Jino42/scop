/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:34:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 18:46:00 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	scene_parse_failed(cJSON *json)
{
	cJSON_Delete(json);
	return (false);
}

bool		scene_parse(t_scene *scene, const char *path)
{
	char			buffer[MAX_SOURCE_SIZE];
	cJSON			*json;

	bzero(buffer, MAX_SOURCE_SIZE);
	if (!(json = json_load_src(path, buffer)))
		return (false);
	if (!(m_material_json_parse(scene->m_texture, scene->m_material,
			json, "material")))
		return (scene_parse_failed(json));
	if (!(m_light_json_parse(scene->m_light, json, "light")))
		return (scene_parse_failed(json));
	if (!(m_shader_json_parse(scene->m_shader, json, "shader")))
		return (scene_parse_failed(json));
	if (!(m_model_json_parse(scene, json, "model")))
		return (scene_parse_failed(json));
	cJSON_Delete(json);
	return (true);
}
