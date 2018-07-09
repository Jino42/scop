#include "scop.h"

t_cam 		*cam_construct()
{
	t_cam *cam;

	if (!(cam = ft_memalloc(sizeof(t_cam))))
		return (NULL);
	cam->projection = matrixgl_get_projection(66.f, (float)WIDTH / (float)HEIGHT, 0.01f, 100.f);
	cam->sensitivity = 0.03f;
	cam->up = vector_construct(0.f, 1.f, 0.f);
	cam->to = vector_construct(0.f, 0.f, 1.f);
	cam->yaw = 90.f;
	cam->position = vector_construct(0.f, 0.f, 1.f);
	cam->front.x = cosf(get_radians(cam->pitch)) * cosf(get_radians(cam->yaw));
	cam->front.y = sinf(get_radians(cam->pitch));
	cam->front.z = sinf(get_radians(cam->yaw));
	vector_normalize(&cam->front);
	return (cam);
}

void		*cam_destruct(t_cam **cam)
{
	ft_memdel((void **)cam);
	return (NULL);
}

static void	cam_update_position(t_cam *cam, const t_glfw *glfw, const float delta_time)
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

static void	cam_update_direction(t_cam *cam)
{
	t_vector offset;
	t_vector *cursor_position;

	cursor_position = singleton_mouse_position();

	if (cursor_position->x != cam->last_cursor_position.x
		|| cursor_position->y != cam->last_cursor_position.y)
	{
		offset.x = (cursor_position->x - cam->last_cursor_position.x);
		offset.y = (cam->last_cursor_position.y - cursor_position->y);
		cam->last_cursor_position = *cursor_position;

		offset.x *= cam->sensitivity;
		offset.y *= cam->sensitivity;

		cam->yaw   += offset.x;
		cam->pitch += offset.y;
		cam->front.x = cosf(get_radians(cam->pitch)) * cosf(get_radians(cam->yaw));
		cam->front.y = sinf(get_radians(cam->pitch));
		cam->front.z = sinf(get_radians(cam->yaw));
		vector_normalize(&cam->front);
	}
}

void		cam_update(t_cam *cam, const t_glfw *glfw, const float delta_time)
{
	cam_update_position(cam, glfw, delta_time);
	cam_update_direction(cam);
	cam->view = matrixgl_view(cam);
}
