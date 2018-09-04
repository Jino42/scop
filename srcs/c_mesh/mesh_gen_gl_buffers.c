/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_gen_gl_buffers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:07:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/04 19:25:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		mesh_gen_gl_buffers_v(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3,
		mesh->indexed_v, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		mesh_gen_gl_buffers_vn(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->VNBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VNBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3,
		mesh->indexed_vn, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		mesh_gen_gl_buffers_vt(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->VTBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VTBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 2,
		mesh->indexed_vt, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		mesh_gen_gl_buffers_color(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->COLORBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->COLORBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * (mesh->nb_indices),
		mesh->indexed_color, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void			mesh_gen_gl_buffers(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->EBO);
	glGenVertexArrays(1, &mesh->VAO);
	glBindVertexArray(mesh->VAO);

	mesh->flag |= SCOP_VN;

	if (mesh->flag & SCOP_V)
		mesh_gen_gl_buffers_v(mesh);
	if (mesh->flag & SCOP_VN)
		mesh_gen_gl_buffers_vn(mesh);
	if (mesh->flag & SCOP_VT)
		mesh_gen_gl_buffers_vt(mesh);
	mesh_gen_gl_buffers_color(mesh);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->nb_indices,
		mesh->indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
