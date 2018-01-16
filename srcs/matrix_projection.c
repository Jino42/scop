/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:51:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/16 22:58:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_matrix matrix_get_projection_opengl(const float fov,
										const float ratio,
										const float near,
										const float far)
{
	t_matrix m;
	float scale, r, t, b, l;

	scale = tanf(fov * 0.5f * M_PI / 180.0f) * near;
	r = ratio * scale;
	l = -r;
    t = scale;
	b = -t;

    m.matrix[0][0] = 2.f * near / (r - l);
    m.matrix[0][1] = 0.f;
    m.matrix[0][2] = 0.f;
    m.matrix[0][3] = 0.f;

    m.matrix[1][0] = 0.f;
    m.matrix[1][1] = 2.f * near / (t - b);
    m.matrix[1][2] = 0.f;
    m.matrix[1][3] = 0.f;

    m.matrix[2][0] = (r + l) / (r - l);
    m.matrix[2][1] = (t + b) / (t - b);
    m.matrix[2][2] = -(far + near) / (far - near);
    m.matrix[2][3] = -1.f;

    m.matrix[3][0] = 0;
    m.matrix[3][1] = 0;
    m.matrix[3][2] = -2.f * far * near / (far - near);
    m.matrix[3][3] = 0;
	return (m);
}
