/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 21:27:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/15 20:39:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef struct	s_matrix
{
	float		matrix[4][4];
}				t_matrix;

t_matrix		matrix_get_identity();
void			matrix_identity(t_matrix *m);

t_matrix		matrix_get_mult_matrix(const t_matrix *a, const t_matrix *b);
t_vector		matrix_get_mult_vector(const t_matrix *m, const t_vector *v);
t_vector		matrix_get_mult_dir_vector(const t_matrix *m,
															const t_vector *v);

t_matrix		matrix_get_rotation_x(const float a);
t_matrix		matrix_get_rotation_y(const float a);
t_matrix		matrix_get_rotation_z(const float a);
t_matrix		matrix_get_translation(const t_vector *trans);
t_matrix		matrix_get_transpose(t_matrix *mn);

void			matrix_rotation_x(t_matrix *m, const float a);
void			matrix_rotation_y(t_matrix *m, const float a);
void			matrix_rotation_z(t_matrix *m, const float a);
void			matrix_translation(t_matrix *m, const t_vector *trans);
void			matrix_transpose(t_matrix *mn);

void			matrix_string(const t_matrix *m);

#endif
