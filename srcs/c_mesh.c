#include "scop.h"

t_mesh		*mesh_construct()
{
	t_mesh *mesh;

	if (!(mesh = ft_memalloc(sizeof(t_mesh))))
		return (NULL);
	mesh->indexed_v = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_vt = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indexed_vn = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ);
	mesh->indices = ft_memalloc(sizeof(GLuint) * BUFFER_OBJ);
	return (mesh);
}

void		*mesh_destruct(t_mesh **mesh)
{
	if (mesh && *mesh)
		ft_memdel((void **)mesh);
	return (NULL);
}

bool			m_mesh_add(t_m_mesh *m_mesh, t_mesh *mesh)
{
	if (!(m_mesh->mesh = realloc(m_mesh->mesh, sizeof(t_mesh **) * (m_mesh->size + 1))))
	{
		m_mesh->size = 0;
		return (false);
	}
	m_mesh->mesh[m_mesh->size] = mesh;
	m_mesh->size++;
	return (true);
}

t_mesh			*m_mesh_new(t_m_mesh *m_mesh)
{
	t_mesh *new;

	if (!(new = mesh_construct()))
		return (NULL);
	if (!(m_mesh->mesh = realloc(m_mesh->mesh, sizeof(t_mesh **) * (m_mesh->size + 1))))
	{
		m_mesh->size = 0;
		return (false);
	}
	m_mesh->mesh[m_mesh->size] = new;
	m_mesh->size++;
	return (new);
}

void	mesh_gen_gl_buffers(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->EBO);
	glGenVertexArrays(1, &mesh->VAO);

	glBindVertexArray(mesh->VAO);

	if (mesh->flag & SCOP_V)
	{
		glGenBuffers(1, &mesh->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3, mesh->indexed_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (mesh->flag & SCOP_VN)
	{
		glGenBuffers(1, &mesh->VNBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VNBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3, mesh->indexed_vn, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (mesh->flag & SCOP_VT)
	{
		glGenBuffers(1, &mesh->VTBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VTBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 2, mesh->indexed_vt, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->nb_indices, mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

t_m_mesh		*m_mesh_construct()
{
	t_m_mesh *m_mesh;

	if (!(m_mesh = ft_memalloc(sizeof(t_m_mesh))))
		return (NULL);
	m_mesh->add = &m_mesh_add;
	m_mesh->new = &m_mesh_new;
	return (m_mesh);
}

void		*m_mesh_destruct(t_m_mesh **m_mesh)
{
	unsigned int i;

	if (m_mesh && *m_mesh)
	{
		if ((*m_mesh)->size)
		{
			i = 0;
			while (i < (*m_mesh)->size)
			{
				mesh_destruct(&(*m_mesh)->mesh[i]);
				i++;
			}
			ft_memdel((void **)&(*m_mesh)->mesh);
		}
		ft_memdel((void **)m_mesh);
	}
	return (NULL);
}
