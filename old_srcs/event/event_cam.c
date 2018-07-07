/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 21:16:27 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/26 23:44:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		event_cam(t_env *e, t_cam *cam, t_glfw *glfw)
{
	t_vector	dir;
	float		speed;

	speed = 1 * e->fps.delta_time;
	if (glfwGetKey(glfw->window, GLFW_KEY_UP) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		dir = vector_get_mult(&cam->to, -speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_DOWN) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		dir = vector_get_mult(&cam->to, speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_LEFT) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		dir = vector_get_cross_product(&e->cam.to, &e->cam.up);
		dir = vector_get_mult(&dir, speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_RIGHT) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		dir = vector_get_cross_product(&e->cam.to, &e->cam.up);
		dir = vector_get_mult(&dir, -speed);
		vector_add(&cam->position, &dir);
	}
}
