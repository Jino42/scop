/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation_y.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:42:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/10 22:44:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_get_rotation_y(const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[2][0] = -sin(a);
	new.matrix[2][2] = cos(a);
	new.matrix[0][2] = sin(a);
	return (new);
}

void		matrix_rotation_y(t_matrix *m, const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[2][0] = -sin(a);
	new.matrix[2][2] = cos(a);
	new.matrix[0][2] = sin(a);
	*m = matrix_get_mult_matrix(m, &new);
	return ;
}

t_matrix	matrixgl_get_rotation_y(const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[0][2] = -sin(a);
	new.matrix[2][2] = cos(a);
	new.matrix[2][0] = sin(a);
	return (new);
}

void		matrixgl_rotation_y(t_matrix *m, const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[0][2] = -sin(a);
	new.matrix[2][2] = cos(a);
	new.matrix[2][0] = sin(a);
	*m = matrix_get_mult_matrix(m, &new);
	return ;
}
