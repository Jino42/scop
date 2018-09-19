/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mult_dir_vector.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:42:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:42:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vector		matrix_get_mult_dir_vector(const t_matrix *m, const t_vector *v)
{
	t_vector n;

	n.x = (v->x * m->matrix[0][0]) + (v->y * m->matrix[0][1]) +
											(v->z * m->matrix[0][2]);
	n.y = (v->x * m->matrix[1][0]) + (v->y * m->matrix[1][1]) +
									(v->z * m->matrix[1][2]);
	n.z = (v->x * m->matrix[2][0]) + (v->y * m->matrix[2][1]) +
									(v->z * m->matrix[2][2]);
	return (n);
}
