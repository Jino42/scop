/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixgl_ortho.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 23:50:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 00:16:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_matrix matrixgl_ortho(const float b, const float t, const float l, const float r, const float n, const float f)
{
	t_matrix matrix;

	matrix = matrix_get_identity();

    matrix.matrix[0][0] = 2 / (r - l);
    matrix.matrix[0][1] = 0;
    matrix.matrix[0][2] = 0;
    matrix.matrix[0][3] = 0;

    matrix.matrix[1][0] = 0;
    matrix.matrix[1][1] = 2 / (t - b);
    matrix.matrix[1][2] = 0;
    matrix.matrix[1][3] = 0;

    matrix.matrix[2][0] = 0;
    matrix.matrix[2][1] = 0;
    matrix.matrix[2][2] = -2 / (f - n);
    matrix.matrix[2][3] = 0;

    matrix.matrix[3][0] = -(r + l) / (r - l);
    matrix.matrix[3][1] = -(t + b) / (t - b);
    matrix.matrix[3][2] = -(f + n) / (f - n);
    matrix.matrix[3][3] = 1;
	return (matrix);
}
