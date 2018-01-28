/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/28 15:22:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	matrix_scaling(t_matrix *m, const float s)
{
	m->matrix[0][0] *= s;
	m->matrix[1][1] *= s;
	m->matrix[2][2] *= s;
}

void	mesh_change_texture(t_env *e, t_mesh *mesh)
{
	e->index_material++;
	e->index_material %= NB_MAT;
	*mesh->material = e->material[e->index_material];
}

bool	render_loop(t_env *e, const char **argv, t_glfw *glfw)
{
	glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw->window, &event_mouse);

	//mesh->light_temp = vector_construct(0.3f, 0.3f, 0.3f);

	t_mesh *mesh_cube = mesh_construct("ressources/cube/cube.obj",
							"ressources/cube/basic.vert",
							"ressources/cube/basic.frag",
							"img/prevo.img");
	t_mesh *mesh = mesh_construct(argv[1],
							"shader/basic.vert",
							"shader/basic.frag",
							"img/prevo.img");
	t_model *teapot, *teapot2, *obj_light;
	t_light *light;

	light = light_construct();
	if (!(obj_light = model_construct(mesh_cube)))
		return (end_of_program(e, "Erreur lors de la création de l'objet", 0));
	t_vector move = vector_construct(0.3f, 0.3f, 0.3f);
	matrix_translation(&obj_light->transform, &move);
	matrix_transpose(&obj_light->transform);
	matrix_scaling(&obj_light->transform, 0.05f);

	if (!(teapot2 = model_construct(mesh)))
		return (end_of_program(e, "Erreur lors de la création de l'objet", 0));
	if (!(teapot = model_construct(mesh)))
		return (end_of_program(e, "Erreur lors de la création de l'objet", 0));
	move = vector_construct(-0.3f, 0, -0.3f);
	matrix_translation(&teapot2->transform, &move);
	matrix_transpose(&teapot2->transform);
	matrix_scaling(&teapot2->transform, 0.05f);

	matrix_scaling(&teapot->transform, 0.005f);

	glEnable(GL_DEPTH_TEST);
	glPointSize(5.0);
//	glShadeModel(GL_SMOOTH);

	t_matrix view, projection;

	projection = matrix_get_projection_opengl(66.f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(glfw->window))
	{
		update_fps(&e->fps);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfw_input(glfw);
		if (glfwGetKey(glfw->window, GLFW_KEY_I) == GLFW_PRESS)
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		event_cam(e, &e->cam, &e->glfw);

		if (glfwGetKey(glfw->window, GLFW_KEY_F) == GLFW_PRESS)
		{
			(teapot->mesh->type_draw == GL_FILL) ? (teapot->mesh->type_draw = GL_LINE) : (teapot->mesh->type_draw = GL_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, teapot->mesh->type_draw);
		}
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_ADD))
			matrix_scaling(&teapot->transform, 1.005f);
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_SUBTRACT))
			matrix_scaling(&teapot->transform, 0.995f);
		if (glfwGetKey(glfw->window, GLFW_KEY_T))
			mesh_change_texture(e, teapot->mesh);
		view = matrix_view(&e->cam);

		obj_light->render(obj_light, &e->cam, light, &view, &projection);
		teapot->render(teapot, &e->cam, light, &view, &projection);
		//teapot2->render(teapot2, &e->cam, &view, &projection);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
	return (true);
}
