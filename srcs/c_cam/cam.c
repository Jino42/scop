/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:21:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 00:23:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_cam		*cam_construct(void)
{
	t_cam *cam;

	if (!(cam = ft_memalloc(sizeof(t_cam))))
		return (NULL);
	cam->fov = 66.f;
	cam->near = 0.01f;
	cam->far = 100.f;
	cam->projection = matrixgl_get_projection(cam->fov,
			(float)WIDTH / (float)HEIGHT, cam->near, cam->far);
	cam->sensitivity = 0.03f;
	cam->up = vector_construct(0.f, 1.f, 0.f);
	cam->to = vector_construct(0.f, 0.f, 1.f);
	cam->yaw = 90.f;
	cam->position = vector_construct(0.f, 0.f, 1.f);
	cam->front.x = cosf(get_radians(cam->pitch)) * cosf(get_radians(cam->yaw));
	cam->front.y = sinf(get_radians(cam->pitch));
	cam->front.z = sinf(get_radians(cam->yaw));
	vector_normalize(&cam->front);
	cam->flag |= CURSOR_NORMAL;
	return (cam);
}

void		*cam_destruct(t_cam **cam)
{
	ft_memdel((void **)cam);
	return (NULL);
}

t_vector	cam_get_front(float pitch, float yaw)
{
	t_vector	vec;

	vec = vector_construct(cosf(get_radians(pitch)) * cosf(get_radians(yaw)),
							sinf(get_radians(pitch)),
							sinf(get_radians(yaw)));
	return (vec);
}
