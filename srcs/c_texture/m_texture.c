#include "scop.h"

bool			m_texture_add(t_m_texture *m_texture, t_texture *texture)
{
	if (!(m_texture->texture = realloc(m_texture->texture,
				sizeof(t_texture **) * (m_texture->size + 1))))
	{
		m_texture->size = 0;
		return (false);
	}
	if (!(m_texture->texture_name = realloc(m_texture->texture_name,
				sizeof(char **) * (m_texture->size + 1))))
	{
		m_texture->size = 0;
		return (false);
	}
	m_texture->texture[m_texture->size] = texture;
	m_texture->texture_name[m_texture->size] = texture->name;
	m_texture->size++;
	return (true);
}

int32_t	texture_exist(t_m_texture *m_texture,
							const char *texture_path)
{
	uint32_t i;

	i = 0;
	while (i < m_texture->size)
	{
		if (!strcmp(texture_path, m_texture->texture[i]->name))
			return (i);
		i++;
	}
	return (-1);
}

t_texture			*m_texture_new(t_m_texture *m_texture,
									const int type,
									const char *texture_path)
{

	int32_t index;
	t_texture *new;

	if ((index = texture_exist(m_texture, texture_path)) != -1)
		return (m_texture->texture[index]);
	if (!(new = texture_construct(texture_path, type)))
		return (NULL);
	if (!(m_texture->texture = realloc(m_texture->texture,
				sizeof(t_texture **) * (m_texture->size + 1))))
	{
		m_texture->size = 0;
		return (false);
	}
	if (!(m_texture->texture_name = realloc(m_texture->texture_name,
				sizeof(char **) * (m_texture->size + 1))))
	{
		m_texture->size = 0;
		return (false);
	}
	m_texture->texture[m_texture->size] = new;
	m_texture->texture_name[m_texture->size] = new->name;
	m_texture->size++;
	return (new);
}

t_m_texture		*m_texture_construct(void)
{
	t_m_texture *m_texture;

	if (!(m_texture = ft_memalloc(sizeof(t_m_texture))))
		return (NULL);
	m_texture->add = &m_texture_add;
	m_texture->new = &m_texture_new;
	return (m_texture);
}

void			*m_texture_destruct(t_m_texture **m_texture)
{
	unsigned int i;

	if (m_texture && *m_texture)
	{
		if ((*m_texture)->size)
		{
			i = 0;
			while (i < (*m_texture)->size)
			{
				texture_destruct(&(*m_texture)->texture[i]);
				i++;
			}
			ft_memdel((void **)&(*m_texture)->texture);
			ft_memdel((void **)&(*m_texture)->texture_name);
		}
		ft_memdel((void **)m_texture);
	}
	return (NULL);
}
