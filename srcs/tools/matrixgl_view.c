/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixgl_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:51:59 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/17 14:13:12 by ntoniolo         ###   ########.fr       */
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
	t_matrix look_at;
	t_matrix translation;

	zaxis = vector_get_sub(position, to);
	vector_normalize(&zaxis);
	xaxis = vector_get_cross_product(up, &zaxis);
	vector_normalize(&xaxis);
	yaxis = vector_get_cross_product(&zaxis, &xaxis);
	look_at = matrix_get_identity();
	translation = matrix_get_identity();
	look_at.matrix[0][0] = xaxis.x;
	look_at.matrix[1][0] = xaxis.y;
	look_at.matrix[2][0] = xaxis.z;
	look_at.matrix[0][1] = yaxis.x;
	look_at.matrix[1][1] = yaxis.y;
	look_at.matrix[2][1] = yaxis.z;
	look_at.matrix[0][2] = zaxis.x;
	look_at.matrix[1][2] = zaxis.y;
	look_at.matrix[2][2] = zaxis.z;
	*((t_vector3f *)&translation.matrix[3][0]) = *((t_vector3f *)position);
	return (matrix_get_mult_matrix(&translation, &look_at));
}
