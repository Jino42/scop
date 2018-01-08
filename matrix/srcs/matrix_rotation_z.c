/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation_z.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:42:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:42:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_get_rotation_z(const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[0][1] = -sin(a);
	new.matrix[1][0] = sin(a);
	new.matrix[1][1] = cos(a);
	return (new);
}

void		matrix_rotation_z(t_matrix *m, const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[0][1] = -sin(a);
	new.matrix[1][0] = sin(a);
	new.matrix[1][1] = cos(a);
	*m = matrix_get_mult_matrix(m, &new);
	return ;
}
