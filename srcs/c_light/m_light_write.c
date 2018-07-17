#include "scop_nk.h"

bool		m_light_write(t_m_light *m_light, cJSON *json_scene)
{
	cJSON			*json_light;
	cJSON			*json_lights;
	t_light		*light;
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
		if (!json_add_vector(json_light, "ambient", &light->ambient) ||
			!json_add_vector(json_light, "diffuse", &light->diffuse) ||
			!json_add_vector(json_light, "specular", &light->specular) ||
			!json_add_vector(json_light, "position", &light->position))
			return (false);
		i++;
	}
	return (true);
}
