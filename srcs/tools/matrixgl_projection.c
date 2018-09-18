/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixgl_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:51:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 00:01:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_matrix	matrixgl_get_projection(const float fov,
									const float ratio,
									const float near,
									const float far)
{
	t_matrix	m;
	float		scale;
	float		r;
	float		t;

	bzero(&m, sizeof(t_matrix));
	scale = tanf(fov * 0.5f * M_PI / 180.0f) * near;
	r = ratio * scale;
	t = scale;
	m.matrix[0][0] = 2.f * near / (r - -r);
	m.matrix[1][1] = 2.f * near / (t - -t);
	m.matrix[2][0] = (r + -r) / (r - -r);
	m.matrix[2][1] = (t + -t) / (t - -t);
	m.matrix[2][2] = -(far + near) / (far - near);
	m.matrix[2][3] = -1.f;
	m.matrix[3][2] = -2.f * far * near / (far - near);
	return (m);
}
