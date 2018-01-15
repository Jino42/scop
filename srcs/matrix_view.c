/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:51:59 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/15 20:53:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_matrix		look_at(const t_vector *position,
						const t_vector *to,
						const t_vector *up)
{
	t_vector zaxis = vector_get_sub(position, to);
	vector_normalize(&zaxis);
	t_vector tmp = vector_get_normalize(up);
    t_vector xaxis = vector_get_cross_product(&tmp, &zaxis);
	vector_normalize(&xaxis);
    t_vector yaxis = vector_get_cross_product(&zaxis, &xaxis);
	t_matrix rotation = matrix_get_identity();
    t_matrix translation = matrix_get_identity();

    rotation.matrix[0][0] = xaxis.x;
    rotation.matrix[1][0] = xaxis.y;
    rotation.matrix[2][0] = xaxis.z;
    rotation.matrix[0][1] = yaxis.x;
    rotation.matrix[1][1] = yaxis.y;
    rotation.matrix[2][1] = yaxis.z;
    rotation.matrix[0][2] = zaxis.x;
    rotation.matrix[1][2] = zaxis.y;
    rotation.matrix[2][2] = zaxis.z;

    translation.matrix[3][0] = position->x;
    translation.matrix[3][1] = position->y;
	translation.matrix[3][2] = position->z;

    return matrix_get_mult_matrix(&translation, &rotation);
}
