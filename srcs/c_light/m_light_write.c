/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_light_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:48:49 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/23 22:51:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	light_json_add_type(t_light *light, cJSON *json_light)
{
	if (light->flag & LIGHT_BASIC && json_add_string(json_light, "type", "basic"))
		return (true);
	else if (light->flag & LIGHT_DIRECTIONNAL && json_add_string(json_light, "type", "directionnal"))
		return (true);
	else if (light->flag & LIGHT_POINT)
	{
		if (!json_add_string(json_light, "type", "point")
			|| !json_add_float(json_light, "constent", light->constent)
			|| !json_add_float(json_light, "linear", light->linear)
			|| !json_add_float(json_light, "quadratic", light->quadratic))
			return (false);
	}
	return (true);
}

bool		m_light_json_write(t_m_light *m_light, cJSON *json_scene)
{
	cJSON			*json_light;
	cJSON			*json_lights;
	t_light			*light;
	unsigned int	i;

	if (!(json_lights = cJSON_CreateArray()))
		return (false);
	cJSON_AddItemToObject(json_scene, "light", json_lights);
	i = 0;
	while (i < m_light->size)
	{
		light = m_light->light[i];
		if (!(json_light = cJSON_CreateObject()))
			return (false);
		cJSON_AddItemToArray(json_lights, json_light);
		if (!json_add_string(json_light, "name", light->name))
			return (false);
		if (!json_add_vector(json_light, "ambient", &light->ambient)
			|| !json_add_vector(json_light, "diffuse", &light->diffuse)
			|| !json_add_vector(json_light, "specular", &light->specular)
			|| !json_add_vector(json_light, "direction", &light->direction)
			|| !json_add_vector(json_light, "position", &light->position))
			return (false);
		if (!light_json_add_type(light, json_light))
			return (false);
		i++;
	}
	return (true);
}
