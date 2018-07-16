#include "scop.h"
#include "cJSON.h"

bool			m_material_json_loop(t_m_material *m_material, cJSON *json_materials)
{
	int				index;
	char			*str;
	cJSON			*json_material;
	t_material		*material;

	if (!json_materials)
		return (ft_bool_error("JSON materials is undefined ", NULL, NULL));
	json_material = json_materials->child;
	index = 0;
	while (json_material)
	{
		str = NULL;
		if (!json_parse_string(json_material, "name", &str))
			return (dprintf(2, "JSON material[%i]: the name is Undefined\n", index) == 0);
		if (!(material = m_material->new(m_material, str)))
			return (false);
		if (!json_parse_vector(json_material, "ambient", &material->ambient))
			return (dprintf(2, "JSON material[%i] %s : ambient error\n", index, material->name) == 0);
		if (!json_parse_vector(json_material, "diffuse", &material->diffuse))
			return (dprintf(2, "JSON material[%i] %s : diffuse error\n", index, material->name) == 0);
		if (!json_parse_vector(json_material, "specular", &material->specular))
			return (dprintf(2, "JSON material[%i] %s : specular error\n", index, material->name) == 0);
		if (!json_parse_float(json_material, "shininess", &material->shininess))
			return (dprintf(2, "JSON material[%i] %s : shininess error\n", index, material->name) == 0);
		json_material = json_material->next;
		index++;
	}
	return (true);
}

bool			m_material_json_parse(t_m_material *m_material, const char *path_material)
{
	char			buffer[MAX_SOURCE_SIZE];
	cJSON			*json;

	bzero(buffer, MAX_SOURCE_SIZE);
	json = json_load_src(path_material, buffer);
	if (!(m_material_json_loop(m_material, json)))
	{
		cJSON_Delete(json);
		return (ft_bool_error("Erreur: Le parsing de t_m_material a échoué", NULL, NULL));
	}
	cJSON_Delete(json);
	return (true);
}

t_material		*material_construct(char *name)
{
	t_material *material;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	material->name = strdup(name);
	return (material);
}

void		*material_destruct(t_material **material)
{
	if (material && *material)
	{
		ft_memdel((void **)(&(*material)->name));
		ft_memdel((void **)material);
	}
	return (NULL);
}

bool			m_material_add(t_m_material *m_material, t_material *material)
{
	if (!(m_material->material = realloc(m_material->material, sizeof(t_material **) * (m_material->size + 1))))
	{
		m_material->size = 0;
		return (false);
	}
	if (!(m_material->material_name = realloc(m_material->material_name, sizeof(char **) * (m_material->size + 1))))
	{
		m_material->size = 0;
		return (false);
	}
	m_material->material[m_material->size] = material;
	m_material->material_name[m_material->size] = material->name;
	m_material->size++;
	return (true);
}

t_material			*m_material_new(t_m_material *m_material, char *name)
{
	t_material *new;

	if (!(new = material_construct(name)))
		return (NULL);
	if (!(m_material->material = realloc(m_material->material, sizeof(t_material **) * (m_material->size + 1))))
	{
		m_material->size = 0;
		return (false);
	}
	if (!(m_material->material_name = realloc(m_material->material_name, sizeof(char **) * (m_material->size + 1))))
	{
		m_material->size = 0;
		return (false);
	}
	m_material->material[m_material->size] = new;
	m_material->material_name[m_material->size] = new->name;
	m_material->size++;
	return (new);
}

t_m_material		*m_material_construct()
{
	t_m_material *m_material;

	if (!(m_material = ft_memalloc(sizeof(t_m_material))))
		return (NULL);
	m_material->add = &m_material_add;
	m_material->new = &m_material_new;
	return (m_material);
}

void		*m_material_destruct(t_m_material **m_material)
{
	unsigned int i;

	if (m_material && *m_material)
	{
		if ((*m_material)->size)
		{
			i = 0;
			while (i < (*m_material)->size)
			{
				material_destruct(&(*m_material)->material[i]);
				i++;
			}
			ft_memdel((void **)&(*m_material)->material);
			ft_memdel((void **)&(*m_material)->material_name);
		}
		ft_memdel((void **)m_material);
	}
	return (NULL);
}

int				m_material_get_index(t_m_material *m_material, char *str)
{
	unsigned int i;

	if (!str || !(*str))
		return (0);
	i = 0;
	while (i < m_material->size)
	{
		printf("%s %s\n", m_material->material[i]->name, str);
		if (!strcmp(m_material->material[i]->name, str))
			return (i);
		i++;
	}
	return (0);
}
