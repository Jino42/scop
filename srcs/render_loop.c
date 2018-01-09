/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/09 22:02:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

void	render_loop(t_env *e, t_glfw *glfw)
{
	while (!glfwWindowShouldClose(glfw->window))
	{
		update_fps(&e->fps);
		glfw_input(glfw);

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
}
