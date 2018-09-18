/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixgl_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:51:59 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 00:13:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_matrix		matrixgl_view(t_cam *cam)
{
	t_vector		dir_look;

	cam->to = cam->front;
	dir_look = vector_get_add(&cam->position, &cam->to);
	return (look_at_gl(&cam->position, &dir_look, &cam->up));
}

t_matrix		look_at_gl(const t_vector *position,
							const t_vector *to,
							const t_vector *up)
{
	t_vector zaxis;
	t_vector xaxis;
	t_vector yaxis;
	t_matrix rotation;
	t_matrix translation;

	zaxis = vector_get_sub(position, to);
	vector_normalize(&zaxis);
	xaxis = vector_get_cross_product(up, &zaxis);
	vector_normalize(&xaxis);
	yaxis = vector_get_cross_product(&zaxis, &xaxis);
	rotation = matrix_get_identity();
	translation = matrix_get_identity();
	rotation.matrix[0][0] = xaxis.x;
	rotation.matrix[1][0] = xaxis.y;
	rotation.matrix[2][0] = xaxis.z;
	rotation.matrix[0][1] = yaxis.x;
	rotation.matrix[1][1] = yaxis.y;
	rotation.matrix[2][1] = yaxis.z;
	rotation.matrix[0][2] = zaxis.x;
	rotation.matrix[1][2] = zaxis.y;
	rotation.matrix[2][2] = zaxis.z;
	*((t_vector3f *)&translation.matrix[3][0]) = *((t_vector3f *)position);
	return (matrix_get_mult_matrix(&translation, &rotation));
}
