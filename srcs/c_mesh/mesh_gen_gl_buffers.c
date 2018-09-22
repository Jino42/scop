/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_gen_gl_buffers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:07:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/22 22:35:42 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		mesh_gen_gl_buffers_v(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3,
		mesh->indexed_v, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		mesh_gen_gl_buffers_vn(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->vnbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vnbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3,
		mesh->indexed_vn, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		mesh_gen_gl_buffers_vt(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->vtbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vtbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 2,
		mesh->indexed_vt, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		mesh_gen_gl_buffers_color(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->colorbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices),
		mesh->indexed_color, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		mesh_gen_gl_buffers_u(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->ubo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->ubo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3,
		mesh->indexed_u, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void			mesh_gen_gl_buffers(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->ebo);
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);
	mesh->flag |= SCOP_VN;
	if (mesh->flag & SCOP_V)
		mesh_gen_gl_buffers_v(mesh);
	if (mesh->flag & SCOP_VN)
		mesh_gen_gl_buffers_vn(mesh);
	if (mesh->flag & SCOP_VT)
		mesh_gen_gl_buffers_vt(mesh);
	else
		mesh_gen_gl_buffers_u(mesh);
	mesh_gen_gl_buffers_color(mesh);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (mesh->nb_indices + mesh->same_indices),
		mesh->indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
