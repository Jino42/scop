/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:28:07 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 16:54:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "scop_nk.h"

bool			loop(t_env *e)
{
	t_glfw		*glfw;

	glfw = e->glfw;
	m_model_setup(e->scene->m_model);
	while (!glfwWindowShouldClose(glfw->window))
	{
		fps_update(e->fps, &e->delta_time);
		e->scene->timestamp = fps_timestamp(e->fps);
		glfw_update(e->glfw);
		m_model_update(e->scene->m_model);
		nk_update(glfw->nk);
		if (!(nk_scene(glfw->nk, &e->scene)))
			return (false);
		cam_update(e->scene->cam, e->glfw, e->delta_time);
		scene_render(e->scene, e->fps->time);
		nk_render(glfw->nk);
		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
	return (true);
}
