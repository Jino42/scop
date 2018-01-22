/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:42:34 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/22 20:22:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_get_translation(const t_vector *trans)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][3] = trans->x;
	new.matrix[1][3] = trans->y;
	new.matrix[2][3] = trans->z;
	return (new);
}

void		matrix_translation(t_matrix *m, const t_vector *trans)
{
	m->matrix[0][3] += trans->x;
	m->matrix[1][3] += trans->y;
	m->matrix[2][3] += trans->z;
	return ;
}
