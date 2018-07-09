/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/09 20:28:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_texture			*texture_3construct()
{
	t_texture			*texture;

	if (!(texture = ft_memalloc(sizeof(t_texture))))
		return (NULL);
	unsigned char *texels = ft_memalloc(WIDTH * HEIGHT * 10 * 4);
	for(int i = 0; i < WIDTH * HEIGHT * 10; i++)
		texels[i] = 255;
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_3D, texture->id);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB8, WIDTH, HEIGHT, 10, 0, GL_RGB,
	             GL_UNSIGNED_BYTE, texels);
	return (texture);
}

/*
void	mesh_change_texture(t_env *e, t_mesh *mesh)
{
	e->index_material++;
	e->index_material %= NB_MAT;
	*mesh->material = e->material[e->index_material];
}
*/
bool	render_loop(t_env *e, const char **argv, t_glfw *glfw)
{
	glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw->window, &event_mouse);
(void)e;
	//mesh->light_temp = vector_construct(0.3f, 0.3f, 0.3f);
	t_model *model;
	model = model_construct(argv[1],
							argv[2],
							NULL);
								//"ressources/Orange_obj/Color.rgb");

	t_shader *shader  = shader_construct("shader/basic.vert",
										"shader/basic.frag");
	matrix_scaling(&model->transform, 0.005f);
	(void)shader;
	t_light *light;

	light = light_construct();

	t_model *obj_light = model_construct("ressources/cube/",
										"ressources/cube/cube.obj",
											NULL);
	t_vector move = vector_construct(0.3f, 0.3f, 0.3f);
	matrix_translation(&obj_light->transform, &move);
	matrix_transpose(&obj_light->transform);
	matrix_scaling(&obj_light->transform, 0.05f);
	//matrix_scaling(&obj_light2->transform, 1.f);

	t_shader *shader_l  = shader_construct("ressources/cube/basic.vert",
										"ressources/cube/basic.frag");(void)shader_l;
	t_shader *shader_f  = shader_construct("ressources/fract/basic.vert",
										"ressources/fract/basic.frag");(void)shader_f;
	t_shader *shader_g  = shader_construct("ressources/tex3/cube/basic.vert",
										"ressources/tex3/cube/basic.frag");(void)shader_g;


	t_matrix projection = matrix_get_projection_opengl(66.f, (float)WIDTH / (float)HEIGHT, 0.01f, 100.f);
	t_matrix view = matrix_view(&e->cam);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glPointSize(5.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(!glfwWindowShouldClose(glfw->window))
	{
		update_fps(&e->fps);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfw_input(glfw);
		if (glfwGetKey(glfw->window, GLFW_KEY_I) == GLFW_PRESS)
			glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		event_cam(e, &e->cam, &e->glfw);
		if (glfwGetKey(glfw->window, GLFW_KEY_F) == GLFW_PRESS)
		{
			(model->type_draw == GL_FILL) ? (model->type_draw = GL_LINE) : (model->type_draw = GL_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, model->type_draw);
		}
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_ADD))
			matrix_scaling(&model->transform, 1.005f);
		if (glfwGetKey(glfw->window, GLFW_KEY_KP_SUBTRACT))
			matrix_scaling(&model->transform, 0.995f);

		view = matrix_view(&e->cam);
		model_render(model, &e->cam, light, &view, &projection, shader);
		model_render(obj_light, &e->cam, light, &view, &projection, shader_l);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
/*
	t_mesh *mesh_cube = mesh_construct("ressources/cube/cube.obj",
							"ressources/cube/basic.vert",
							"ressources/cube/basic.frag",
							"img/prevo.img");
	t_mesh *mesh = mesh_construct(argv[1],
							"shader/basic.vert",
							"shader/basic.frag",
							"ressources/Orange_obj/Color.rgb");
	t_model *teapot, *teapot2, *obj_light;
	t_light *light;

	if (!(teapot2 = model_construct(mesh)))
		return (end_of_program(e, "Erreur lors de la création de l'objet", 0));
	if (!(teapot = model_construct(mesh)))
		return (end_of_program(e, "Erreur lors de la création de l'objet", 0));
	move = vector_construct(-0.3f, 0, -0.3f);
	matrix_translation(&teapot2->transform, &move);
	matrix_transpose(&teapot2->transform);
	matrix_scaling(&teapot2->transform, 0.05f);

	matrix_scaling(&teapot->transform, 0.005f);

//	glShadeModel(GL_SMOOTH);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(glfw->window))
	{

		if (glfwGetKey(glfw->window, GLFW_KEY_T))
			mesh_change_texture(e, teapot->mesh);
	}*/
	return (true);
}
