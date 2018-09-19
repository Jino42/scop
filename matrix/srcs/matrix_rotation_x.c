/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:42:28 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/10 14:14:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_get_rotation_x(const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[1][1] = cos(a);
	new.matrix[2][2] = cos(a);
	new.matrix[1][2] = -sin(a);
	new.matrix[2][1] = sin(a);
	return (new);
}

void		matrix_rotation_x(t_matrix *m, const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[1][1] = cos(a);
	new.matrix[2][2] = cos(a);
	new.matrix[1][2] = -sin(a);
	new.matrix[2][1] = sin(a);
	*m = matrix_get_mult_matrix(m, &new);
	return ;
}

t_matrix	matrixgl_get_rotation_x(const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[1][1] = cos(a);
	new.matrix[2][2] = cos(a);
	new.matrix[2][1] = -sin(a);
	new.matrix[1][2] = sin(a);
	return (new);
}

void		matrixgl_rotation_x(t_matrix *m, const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[1][1] = cos(a);
	new.matrix[2][2] = cos(a);
	new.matrix[2][1] = -sin(a);
	new.matrix[1][2] = sin(a);
	*m = matrix_get_mult_matrix(m, &new);
	return ;
}
