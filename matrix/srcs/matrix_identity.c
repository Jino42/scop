/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_identity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:42:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:43:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix		matrix_get_identity(void)
{
	t_matrix m;

	m.matrix[0][0] = 1;
	m.matrix[0][1] = 0;
	m.matrix[0][2] = 0;
	m.matrix[0][3] = 0;
	m.matrix[1][0] = 0;
	m.matrix[1][1] = 1;
	m.matrix[1][2] = 0;
	m.matrix[1][3] = 0;
	m.matrix[2][0] = 0;
	m.matrix[2][1] = 0;
	m.matrix[2][2] = 1;
	m.matrix[2][3] = 0;
	m.matrix[3][0] = 0;
	m.matrix[3][1] = 0;
	m.matrix[3][2] = 0;
	m.matrix[3][3] = 1;
	return (m);
}

void			matrix_identity(t_matrix *m)
{
	m->matrix[0][0] = 1;
	m->matrix[0][1] = 0;
	m->matrix[0][2] = 0;
	m->matrix[0][3] = 0;
	m->matrix[1][0] = 0;
	m->matrix[1][1] = 1;
	m->matrix[1][2] = 0;
	m->matrix[1][3] = 0;
	m->matrix[2][0] = 0;
	m->matrix[2][1] = 0;
	m->matrix[2][2] = 1;
	m->matrix[2][3] = 0;
	m->matrix[3][0] = 0;
	m->matrix[3][1] = 0;
	m->matrix[3][2] = 0;
	m->matrix[3][3] = 1;
}
