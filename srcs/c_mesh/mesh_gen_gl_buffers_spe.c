/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_gen_gl_buffers_spe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:23:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 20:24:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		mesh_gen_gl_buffers_color(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->colorbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices),
		mesh->indexed_color, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void		mesh_gen_gl_buffers_u(t_mesh *mesh)
{
	glGenBuffers(1, &mesh->ubo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->ubo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (mesh->nb_indices) * 3,
		mesh->indexed_u, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
