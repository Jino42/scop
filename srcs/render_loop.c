/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/21 21:12:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

//VertexsBufferObject : Vertex, Coordonates, Textures, -> RAM
//VertexArrayObject : tableau de reference of VBO
//ElementBufferObject :

bool	render_loop(t_env *e, const char **argv, t_glfw *glfw)
{
	glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw->window, &event_mouse);

	t_model *teapot;

	if (!(teapot = model_construct(argv[1],
							"shader/basic.vert",
							"shader/basic.frag")))
		return (end_of_program(e, "Erreur lors de la création de l'objet", 0));

	glEnable(GL_DEPTH_TEST);
	glPointSize(5.0);

	t_matrix view, projection;

	projection = matrix_get_projection_opengl(66.f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);

	while (!glfwWindowShouldClose(glfw->window))
	{
		update_fps(&e->fps);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfw_input(glfw);
		if (glfwGetKey(glfw->window, GLFW_KEY_I) == GLFW_PRESS)
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		event_cam(e, &e->cam, &e->glfw);

		if (glfwGetKey(glfw->window, GLFW_KEY_F))
		{
			(teapot->asset->type_draw == GL_FILL) ? (teapot->asset->type_draw = GL_LINE) : (teapot->asset->type_draw = GL_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, teapot->asset->type_draw);
		}
		view = matrix_view(&e->cam);

		teapot->render(teapot, &view, &projection);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
	return (true);
}
