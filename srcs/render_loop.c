/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/02/10 00:23:04 by ntoniolo         ###   ########.fr       */
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

void	matrix_scaling(t_matrix *m, const float s)
{
	m->matrix[0][0] *= s;
	m->matrix[1][1] *= s;
	m->matrix[2][2] *= s;
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

//	if (argv[3])
//		if (!parsing_mtl(model, argv[3]))
//			return (0);
	t_shader *shader  = shader_construct("shader/basic.vert",
										"shader/basic.frag");
	matrix_scaling(&model->transform, 0.005f);
	(void)shader;
	t_light *light;

	light = light_construct();

	t_model *obj_light = model_construct("ressources/cube/",
										"ressources/cube/cube.obj",
											NULL);
	t_model *obj_f = model_construct("ressources/fract/",
										"ressources/fract/cub.obj",
											NULL);
	if(!obj_f)
		exit(0);
	t_vector move = vector_construct(0.3f, 0.3f, 0.3f);
	matrix_translation(&obj_light->transform, &move);
	matrix_transpose(&obj_light->transform);
	matrix_scaling(&obj_light->transform, 0.05f);

	t_shader *shader_l  = shader_construct("ressources/cube/basic.vert",
										"ressources/cube/basic.frag");
	t_shader *shader_f  = shader_construct("ressources/fract/basic.vert",
										"ressources/fract/basic.frag");(void)shader_f;
	t_shader *shader_g  = shader_construct("ressources/tex3/cube/basic.vert",
										"ressources/tex3/cube/basic.frag");(void)shader_g;


	t_matrix projection = matrix_get_projection_opengl(66.f, (float)WIDTH / (float)HEIGHT, 0.01f, 100.f);
	t_matrix view = matrix_view(&e->cam);

	t_texture *tex3d = texture_3construct();



	glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	(void)tex3d;
	float vertices[] = {
        // positions          // colors           // texture coords
        0.f, 0.f, 0.f,  0.f, 0.f, 0.f,
        0.f, 0.f, 1.f,  0.f, 0.f, 1.f,
        0.f, 1.f, 0.f,  0.f, 1.f, 0.f,
    	0.f, 1.f, 1.f,  0.f, 1.f, 1.f,
		1.f, 0.f, 0.f,  1.f, 0.f, 0.f,
		1.f, 0.f, 1.f,  1.f, 0.f, 1.f,
	   	1.f, 1.f, 0.f,  1.f, 1.f, 0.f,
	   	1.f, 1.f, 1.f,  1.f, 1.f, 1.f,
    };
	unsigned int indices[] = {
        0, 6, 4, // first triangle
		0, 6, 2,  // second triangle
		0, 3, 2,  // second triangle
        0, 1, 3,  // second triangle
		2, 7, 6,
		2, 3, 7,
		4, 6, 7,
		4, 7, 5,
		0, 4, 5,
		0, 5, 1,
		1, 5, 7,
		1, 7, 3
    };
	unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    // texture coord attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

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
		//model_render(obj_f, &e->cam, light, &view, &projection, shader_f);



        // render container
        shader_g->use(shader_g);
		t_matrix temp = matrix_get_mult_matrix(&model->transform, &view);
		t_matrix mvp = matrix_get_mult_matrix(&temp, &projection);
		glUniform3fv(
				glGetUniformLocation(shader_g->program, "light.ambient"),
				1,
				(GLfloat *)&light->ambient);
		glUniform3fv(
				glGetUniformLocation(shader_g->program, "light.diffuse"),
				1,
				(GLfloat *)&light->diffuse);
		glUniform3fv(
				glGetUniformLocation(shader_g->program, "light.specular"),
				1,
				(GLfloat *)&light->specular);
		glUniform3fv(
				glGetUniformLocation(shader_g->program, "light.position"),
				1,
				(GLfloat *)&light->position);
		glUniform3f(
				glGetUniformLocation(shader_g->program, "cameraPosition"),
				e->cam.position.x,
				e->cam.position.y,
				e->cam.position.z);
		glUniform3f(
				glGetUniformLocation(shader_g->program, "camDir"),
				e->cam.to.x,
				e->cam.to.y,
				e->cam.to.z);
		glUniformMatrix4fv(
				glGetUniformLocation(shader_g->program, "MVP"),
				1, GL_FALSE, &mvp.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader_g->program, "V"),
				1, GL_FALSE, &view.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader_g->program, "P"),
				1, GL_FALSE, &projection.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader_g->program, "M"),
				1, GL_FALSE, &model->transform.matrix[0][0]);
				glUniform1i(glGetUniformLocation(shader_g->program, "tex3d"), 0);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_3D, tex3d->id);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0);





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
