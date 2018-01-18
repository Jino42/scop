/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:34:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/18 22:44:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_event_camfps		*singleton_mouse()
{
	static t_event_camfps a = {0.f, -90.f, {0.f, 0.f, 0.f, 0.f}};
	return (&a);
}

void				event_mouse(GLFWwindow *window, double pos_x, double pos_y)
{
	(void)window;
	float sensitivity = 0.05;
	static bool first_callback = true;
	static float last_x = WIDTH/2, last_y = HEIGHT/2;
	t_event_camfps *camfps;

	camfps = singleton_mouse();
	if (first_callback)
	{
		last_x = pos_x;
		last_y = pos_y;
		first_callback = false;
	}

	float offset_x = (pos_x - last_x);
	float offset_y = (last_y - pos_y);
	last_x = pos_x;
	last_y = pos_y;

	offset_x *= sensitivity;
	offset_y *= sensitivity;

	camfps->yaw   += offset_x;
	camfps->pitch += offset_y;
	camfps->front.x = cosf(get_radians(camfps->pitch)) * cosf(get_radians(camfps->yaw));
	camfps->front.y = sinf(get_radians(camfps->pitch));
	camfps->front.z = sinf(get_radians(camfps->yaw));
	vector_normalize(&camfps->front);
}
