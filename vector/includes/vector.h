/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 22:14:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:41:14 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdbool.h>

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector;

t_vector		vector_construct(const float x, const float y, const float z);

void			vector_clear(t_vector *a);

void			vector_normalize(t_vector *vec);
void			vector_abs(t_vector *a);
void			vector_floor(t_vector *a);
void			vector_add(t_vector *a, const t_vector *b);
void			vector_sub(t_vector *a, const t_vector *b);
void			vector_scale(t_vector *a, const t_vector *b);
void			vector_mult(t_vector *a, const float mult);
void			vector_div(t_vector *a, const float div);
void			vector_copy(t_vector *a, const t_vector *b);
void			vector_invert(t_vector *vec);
void			vector_rotate_z(t_vector *a, const float angle);
void			vector_rotate_y(t_vector *a, const float angle);
void			vector_rotate_x(t_vector *a, const float angle);
void			vector_limit(t_vector *a, const float limit);
void			vector_inverse_rotate(t_vector *this, const t_vector *rot);
void			vector_rotate(t_vector *this, const t_vector *rot);

bool			vector_aequals(const t_vector *a, const t_vector *b);
bool			vector_is_zero(const t_vector *a);
float			vector_distance(const t_vector *a, const t_vector *b);
float			vector_magnitude(const t_vector *vec);
float			vector_sqrt_magnitude(const t_vector *vec);
float			vector_dot(const t_vector *a, const t_vector *b);

t_vector		vector_get_normalize(const t_vector *vec);
t_vector		vector_get_add(const t_vector *a, const t_vector *b);
t_vector		vector_get_sub(const t_vector *a, const t_vector *b);
t_vector		vector_get_scale(const t_vector *a, const t_vector *b);
t_vector		vector_get_mult(const t_vector *a, const float mult);
t_vector		vector_get_div(const t_vector *a, const float div);
t_vector		vector_get_copy(const t_vector *a);
t_vector		vector_get_floor(const t_vector *a);
t_vector		vector_get_abs(const t_vector *a);
t_vector		vector_get_invert(const t_vector *vec);
t_vector		vector_get_rotate_z(const t_vector *a, const float angle);
t_vector		vector_get_rotate_y(const t_vector *a, const float angle);
t_vector		vector_get_rotate_x(const t_vector *a, const float angle);
t_vector		vector_get_inverse_rotate(const t_vector *this,
													const t_vector *rot);
t_vector		vector_get_rotate(const t_vector *this, const t_vector *rot);

t_vector		vector_lerp(const t_vector *a,
										const t_vector *b, const float t);
t_vector		vector_lerp_unclamped(const t_vector *a,
										const t_vector *b, const float t);
t_vector		vector_move_towards(const t_vector *a,
										const t_vector *b, const float t);
t_vector		vector_get_cross_product(const t_vector *a,
										const t_vector *b);
void			vector_cross_product(t_vector *a, const t_vector *b);

#endif
