/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_light_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:48:44 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 00:37:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool			m_light_json_loop_parse_3(cJSON *json_light,
											t_light *light,
											int index)
{
	char			*str;

	(void)index;
	if (json_parse_string(json_light, "type", &str))
	{
		if (!strcmp("directionnal", str))
			light->flag |= LIGHT_DIRECTIONNAL;
		else if (!strcmp("point", str))
			light->flag |= LIGHT_POINT;
		else
			light->flag |= LIGHT_BASIC;
	}
	else
		light->flag |= LIGHT_BASIC;
	if (!json_parse_float(json_light, "constent", &light->constent))
		light->constent = 1.f;
	if (!json_parse_float(json_light, "linear", &light->linear))
		light->linear = 0.045f;
	if (!json_parse_float(json_light, "quadratic", &light->quadratic))
		light->quadratic = 0.0075f;
	if (!json_parse_float(json_light, "intensity", &light->intensity))
		light->quadratic = 1.f;
	return (true);
}

static bool			m_light_json_loop_parse_2(cJSON *json_light,
											t_light *light,
											int index)
{
	if (!json_parse_vector(json_light, "ambient", &light->ambient))
	{
		return (dprintf(2, "JSON light[%i] %s : ambient error\n",
				index, light->name) == 0);
	}
	if (!json_parse_vector(json_light, "diffuse", &light->diffuse))
	{
		return (dprintf(2, "JSON light[%i] %s : diffuse error\n",
				index, light->name) == 0);
	}
	if (!json_parse_vector(json_light, "specular", &light->specular))
	{
		return (dprintf(2, "JSON light[%i] %s : specular error\n",
				index, light->name) == 0);
	}
	if (!json_parse_vector(json_light, "position", &light->position))
		light->position = vector_construct(0.f, 0.f, 0.f);
	if (!json_parse_vector(json_light, "direction", &light->direction))
		light->rotation = vector_construct(0.f, 0.f, 0.f);
	light->direction = vector_construct(0.f, 0.f, -1.f);
	vector_normalize(&light->direction);
	m_light_json_loop_parse_3(json_light, light, index);
	return (true);
}

static bool			m_light_json_loop_parse(cJSON *json_light,
											t_m_light *m_light,
											int index)
{
	char			*str;
	t_light			*light;

	str = NULL;
	if (!json_parse_string(json_light, "name", &str))
	{
		return (dprintf(2, "JSON light[%i]: the name is Undefined\n",
				index) == 0);
	}
	if (!(light = m_light->new(m_light, str)))
		return (false);
	if (!(m_light_json_loop_parse_2(json_light, light, index)))
		return (false);
	return (true);
}

static bool			m_light_json_loop(t_m_light *m_light, cJSON *json_lights)
{
	int				index;
	cJSON			*json_light;

	if (!json_lights)
		return (ft_bool_error("JSON lights is undefined ", NULL, NULL));
	json_light = json_lights->child;
	index = 0;
	while (json_light)
	{
		if (!(m_light_json_loop_parse(json_light, m_light, index)))
			return (false);
		json_light = json_light->next;
		index++;
	}
	return (true);
}

bool				m_light_json_parse(t_m_light *m_light,
										cJSON *get,
										const char *key)
{
	cJSON	*source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!(m_light_json_loop(m_light, source)))
	{
		return (ft_bool_error("Erreur: Le parsing de t_m_light a échoué",
				NULL, NULL));
	}
	return (true);
}
