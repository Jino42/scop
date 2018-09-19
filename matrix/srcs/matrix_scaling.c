/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scaling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 23:13:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/25 13:39:53 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	matrix_scaling(t_matrix *m, const float s)
{
	m->matrix[0][0] *= s;
	m->matrix[1][1] *= s;
	m->matrix[2][2] *= s;
}

t_matrix	matrix_get_scaling(t_matrix *m, const float s)
{
	t_matrix	new;

	new = *m;
	new.matrix[0][0] *= s;
	new.matrix[1][1] *= s;
	new.matrix[2][2] *= s;
	return (new);
}


void	matrix_vector_scaling(t_matrix *m, t_vector *vec)
{
	m->matrix[0][0] *= vec->x;
	m->matrix[1][1] *= vec->y;
	m->matrix[2][2] *= vec->z;
}
