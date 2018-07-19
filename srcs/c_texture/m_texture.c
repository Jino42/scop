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

t_texture			*m_texture_new(t_m_texture *m_texture, char *name)
{
	t_texture *new;

	if (!(new = texture_construct(name)))
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
