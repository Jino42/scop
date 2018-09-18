/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:22:07 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 00:26:12 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			cam_update_position_2(t_cam *cam,
										const t_glfw *glfw,
										const float delta_time)
{
	t_vector	dir;
	float		speed;

	speed = 1 * delta_time;
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
}

static void			cam_update_position_1(t_cam *cam,
										const t_glfw *glfw,
										const float delta_time)
{
	t_vector	dir;
	float		speed;

	speed = 1 * delta_time;
	if (glfwGetKey(glfw->window, GLFW_KEY_LEFT) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		dir = vector_get_cross_product(&cam->to, &cam->up);
		dir = vector_get_mult(&dir, speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_RIGHT) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		dir = vector_get_cross_product(&cam->to, &cam->up);
		dir = vector_get_mult(&dir, -speed);
		vector_add(&cam->position, &dir);
	}
}

static void			cam_update_direction(t_cam *cam)
{
	t_vector offset;
	t_vector *cursor_position;

	cursor_position = singleton_mouse_position();
	if (cursor_position->x != cam->last_cursor_position.x
		|| cursor_position->y != cam->last_cursor_position.y)
	{
		if (!cam->first_callback)
		{
			cam->last_cursor_position = *cursor_position;
			cam->first_callback = true;
			return ;
		}
		offset.x = (cursor_position->x - cam->last_cursor_position.x);
		offset.y = (cam->last_cursor_position.y - cursor_position->y);
		cam->last_cursor_position = *cursor_position;
		offset.x *= cam->sensitivity;
		offset.y *= cam->sensitivity;
		cam->yaw += offset.x;
		cam->pitch += offset.y;
		cam->front.x = cosf(get_radians(cam->pitch))
			* cosf(get_radians(cam->yaw));
		cam->front.y = sinf(get_radians(cam->pitch));
		cam->front.z = sinf(get_radians(cam->yaw));
	}
}

void				cam_update(t_cam *cam,
								const t_glfw *glfw,
								const float delta_time)
{
	cam_update_position_1(cam, glfw, delta_time);
	cam_update_position_2(cam, glfw, delta_time);
	if (cam->fps)
		cam_update_direction(cam);
	cam->view = matrixgl_view(cam);
	if (glfw->key[GLFW_KEY_SPACE])
	{
		glfw->key[GLFW_KEY_SPACE] = false;
		if (cam->flag & CURSOR_NORMAL)
		{
			cam->fps = true;
			cam->flag ^= CURSOR_NORMAL;
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			cam->fps = false;
			cam->flag |= CURSOR_NORMAL;
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		cam->first_callback = false;
	}
}
