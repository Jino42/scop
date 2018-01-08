/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:35:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void		vector_rotate(t_vector *this, const t_vector *rot)
{
	vector_rotate_x(this, rot->x);
	vector_rotate_y(this, rot->y);
	vector_rotate_z(this, rot->z);
}

void		vector_inverse_rotate(t_vector *this, const t_vector *rot)
{
	vector_rotate_z(this, -rot->z);
	vector_rotate_y(this, -rot->y);
	vector_rotate_x(this, -rot->x);
}

t_vector	vector_get_rotate(const t_vector *this, const t_vector *rot)
{
	t_vector n;

	n = *this;
	if (rot->x)
		vector_rotate_x(&n, rot->x);
	if (rot->y)
		vector_rotate_y(&n, rot->y);
	if (rot->z)
		vector_rotate_z(&n, rot->z);
	return (n);
}

t_vector	vector_get_inverse_rotate(const t_vector *this, const t_vector *rot)
{
	t_vector n;

	n = *this;
	if (-rot->z)
		vector_rotate_z(&n, -rot->z);
	if (-rot->y)
		vector_rotate_y(&n, -rot->y);
	if (-rot->x)
		vector_rotate_x(&n, -rot->x);
	return (n);
}
