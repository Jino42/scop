/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shader_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:26:34 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:37:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		m_shader_json_write(t_m_shader *m_shader, cJSON *json_scene)
{
	cJSON			*json_shader;
	cJSON			*json_shaders;
	t_shader		*shader;
	unsigned int	i;

	if (!(json_shaders = cJSON_CreateArray()))
		return (false);
	cJSON_AddItemToObject(json_scene, "shader", json_shaders);
	i = 0;
	while (i < m_shader->size)
	{
		shader = m_shader->shader[i];
		if (!(json_shader = cJSON_CreateObject()))
			return (false);
		cJSON_AddItemToArray(json_shaders, json_shader);
		if (!json_add_string(json_shader, "name", shader->name) ||
			!json_add_string(json_shader, "vertex", shader->path_vertex) ||
			!json_add_string(json_shader, "fragment", shader->path_fragment))
			return (false);
		i++;
	}
	return (true);
}
