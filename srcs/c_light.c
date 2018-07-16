#include "scop.h"
#include "cJSON.h"

bool			m_light_json_loop(t_m_light *m_light, cJSON *json_lights)
{
	int				index;
	char			*str;
	cJSON			*json_light;
	t_light			*light;

	if (!json_lights)
		return (ft_bool_error("JSON lights is undefined ", NULL, NULL));
	json_light = json_lights->child;
	index = 0;
	while (json_light)
	{
		str = NULL;
		if (!json_parse_string(json_light, "name", &str))
			return (dprintf(2, "JSON light[%i]: the name is Undefined\n", index) == 0);
		if (!(light = m_light->new(m_light, str)))
			return (false);
		if (!json_parse_vector(json_light, "ambient", &light->ambient))
			return (dprintf(2, "JSON light[%i] %s : ambient error\n", index, light->name) == 0);
		if (!json_parse_vector(json_light, "diffuse", &light->diffuse))
			return (dprintf(2, "JSON light[%i] %s : diffuse error\n", index, light->name) == 0);
		if (!json_parse_vector(json_light, "specular", &light->specular))
			return (dprintf(2, "JSON light[%i] %s : specular error\n", index, light->name) == 0);
		if (!json_parse_vector(json_light, "position", &light->position))
			return (dprintf(2, "JSON light[%i] %s : position error\n", index, light->name) == 0);
		json_light = json_light->next;
		index++;
	}
	return (true);
}

bool			m_light_json_parse(t_m_light *m_light, cJSON *get, const char *key)
{
	cJSON	*source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!(m_light_json_loop(m_light, source)))
		return (ft_bool_error("Erreur: Le parsing de t_m_light a échoué", NULL, NULL));
	return (true);
}

t_light		*light_construct(char *name)
{
	t_light *light;

	if (!(light = ft_memalloc(sizeof(t_light))))
		return (NULL);
	light->name = strdup(name);
	return (light);
}

void		*light_destruct(t_light **light)
{
	if (light && *light)
	{
		ft_memdel((void **)(&(*light)->name));
		ft_memdel((void **)light);
	}
	return (NULL);
}

bool			m_light_add(t_m_light *m_light, t_light *light)
{
	if (!(m_light->light = realloc(m_light->light, sizeof(t_light **) * (m_light->size + 1))))
	{
		m_light->size = 0;
		return (false);
	}
	if (!(m_light->light_name = realloc(m_light->light_name, sizeof(char **) * (m_light->size + 1))))
	{
		m_light->size = 0;
		return (false);
	}
	m_light->light[m_light->size] = light;
	m_light->light_name[m_light->size] = light->name;
	m_light->size++;
	return (true);
}

t_light			*m_light_new(t_m_light *m_light, char *name)
{
	t_light *new;

	if (!(new = light_construct(name)))
		return (NULL);
	if (!(m_light->light = realloc(m_light->light, sizeof(t_light **) * (m_light->size + 1))))
	{
		m_light->size = 0;
		return (false);
	}
	if (!(m_light->light_name = realloc(m_light->light_name, sizeof(char **) * (m_light->size + 1))))
	{
		m_light->size = 0;
		return (false);
	}
	m_light->light[m_light->size] = new;
	m_light->light_name[m_light->size] = new->name;
	m_light->size++;
	return (new);
}

t_m_light		*m_light_construct()
{
	t_m_light *m_light;

	if (!(m_light = ft_memalloc(sizeof(t_m_light))))
		return (NULL);
	m_light->add = &m_light_add;
	m_light->new = &m_light_new;
	return (m_light);
}

void		*m_light_destruct(t_m_light **m_light)
{
	unsigned int i;

	if (m_light && *m_light)
	{
		if ((*m_light)->size)
		{
			i = 0;
			while (i < (*m_light)->size)
			{
				light_destruct(&(*m_light)->light[i]);
				i++;
			}
			ft_memdel((void **)&(*m_light)->light);
			ft_memdel((void **)&(*m_light)->light_name);
		}
		ft_memdel((void **)m_light);
	}
	return (NULL);
}
