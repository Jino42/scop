/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mult_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:42:26 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:43:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vector		matrix_get_mult_vector(const t_matrix *m, const t_vector *v)
{
	t_vector	new;
	float		len;

	new.x = (m->matrix[0][0] * v->x) + (m->matrix[0][1] * v->y) +
								(m->matrix[0][2] * v->z) + (m->matrix[0][3]);
	new.y = (m->matrix[1][0] * v->x) + (m->matrix[1][1] * v->y) +
								(m->matrix[1][2] * v->z) + (m->matrix[1][3]);
	new.z = (m->matrix[2][0] * v->x) + (m->matrix[2][1] * v->y) +
								(m->matrix[2][2] * v->z) + (m->matrix[2][3]);
	len = (m->matrix[3][0] * v->x) + (m->matrix[3][1] * v->y) +
								(m->matrix[3][2] * v->z) + (m->matrix[3][3]);
	new.x /= len;
	new.y /= len;
	new.z /= len;
	return (new);
}
