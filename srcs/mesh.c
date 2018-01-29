/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 21:13:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/29 23:35:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
static void		mesh_buffers(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->EBO);
	glGenVertexArrays(1, &mesh->VAO);

	glBindVertexArray(mesh->VAO);

	if (mesh->flag & SCOP_V)
	{
		ft_printf("Set buffer : V\n");
		glGenBuffers(1, &mesh->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3, mesh->indexed_v, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (mesh->flag & SCOP_VN)
	{
		ft_printf("Set buffer : VN\n");
		glGenBuffers(1, &mesh->VNBO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VNBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3, mesh->indexed_vn, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (mesh->flag & SCOP_VT)
	{
		ft_printf("Set buffer : VT\n");
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
}*/
/*
void	*mesh_destroy(t_mesh **mesh)
{
	if (!mesh || !*mesh)
		return (NULL);

	if ((*mesh)->shader)
		shader_destroy(&(*mesh)->shader);
	if ((*mesh)->texture)
		texture_destroy(&(*mesh)->texture);
	glDeleteBuffers(1, &(*mesh)->VBO);
	glDeleteBuffers(1, &(*mesh)->VNBO);
	glDeleteBuffers(1, &(*mesh)->VTBO);
	glDeleteBuffers(1, &(*mesh)->EBO);
	glDeleteVertexArrays(1, &(*mesh)->VAO);
	ft_memdel((void *)&(*mesh)->v);
	ft_memdel((void *)&(*mesh)->vt);
	ft_memdel((void *)&(*mesh)->vn);
	ft_memdel((void *)&(*mesh)->indexed_v);
	ft_memdel((void *)&(*mesh)->indexed_vt);
	ft_memdel((void *)&(*mesh)->indexed_vn);
	ft_memdel((void *)mesh);
	return (NULL);
}

static void		mesh_debug(t_mesh *mesh)
{
	int fd = open("osef", O_RDWR | O_TRUNC);
	int i = 0;
	while (i < mesh->nb_v)
	{
		dprintf(fd, "v %.6f %.6f %.6f\n", mesh->v[i * 3], mesh->v[i * 3 + 1], mesh->v[i * 3 + 2]);
		i++;
	}
	i = 0;
	while (i < mesh->nb_vt)
	{
		dprintf(fd, "vt %.4f %.4f\n", mesh->vt[i * 2], mesh->vt[i * 2 + 1]);
		i++;
	}
	i = 0;
	while (i < mesh->nb_vn)
	{
		dprintf(fd, "vn %.4f %.4f %.4f\n", mesh->vn[i * 3], mesh->vn[i * 3 + 1], mesh->vn[i * 3 + 2]);
		i++;
	}
	i = 0;
	while (i < mesh->nb_indices)
	{
		dprintf(fd, "v %f %f %f\n",
		mesh->indexed_v[i],
		mesh->indexed_v[i+1],
		mesh->indexed_v[i+2]);
		i+=3;
	}
	dprintf(fd, "%d\n", mesh->nb_v);
	dprintf(fd, "%d\n", mesh->nb_indices);
	dprintf(fd, "%d\n", mesh->nb_faces);
}

t_mesh	*mesh_construct(const char *path_obj,
						const char *shader_vert_path,
						const char *shader_frag_path,
						const char *texture_path)
{
	t_mesh		*mesh;

	if (!(mesh = ft_memalloc(sizeof(t_mesh))))
		return (NULL);
	if (!obj_pars(mesh, path_obj))
	{
		ft_memdel((void *)&mesh);
		return (NULL);
	}
	if (DEBUG)
		mesh_debug(mesh);
	mesh_buffers(mesh);
	if (!(mesh->shader = shader_construct(shader_vert_path, shader_frag_path)))
		return (NULL);
	if (!(mesh->material = material_construct()))
		return (NULL);
	if (texture_path)
	{
		mesh->flag |= F_TEXTURE;
		if (!(mesh->texture = texture_construct(texture_path)))
			return (NULL); ////////DAFUQ
		mesh->shader->use(mesh->shader);
		glUniform1i(glGetUniformLocation(mesh->shader->program, "testTexture"), 0);
	}
	return (mesh);
}
*/
