/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/19 23:25:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

//VertexsBufferObject : Vertex, Coordonates, Textures, -> RAM
//VertexArrayObject : tableau de reference of VBO
//ElementBufferObject :

void		model_render(t_model *model, t_matrix *view, t_matrix *projection)
{
	t_asset *asset;
	t_matrix temp, mvp;

	asset = model->asset;
	asset->shader.use(&asset->shader);
	temp = matrix_get_mult_matrix(&model->transform, view);
	mvp = matrix_get_mult_matrix(&temp, projection);
	glUniformMatrix4fv(
			glGetUniformLocation(asset->shader.program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);

	glBindVertexArray(asset->VAO);
	glDrawElements(asset->type_draw, asset->nb_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

bool		asset_texture(t_asset *asset, const char *texture_path)
{
	if (!import_texture(&asset->texture, texture_path))
		return (false);
	glGenTextures(1, &asset->textureID);
	glBindTexture(GL_TEXTURE_2D, asset->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
								asset->texture.width,
								asset->texture.height,
								0, GL_RGBA, GL_UNSIGNED_BYTE,
								asset->texture.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (true);
}
void		asset_buffers(t_asset *asset)
{
	glGenBuffers(1, &asset->EBO);
	glGenBuffers(1, &asset->VBO);
	glGenVertexArrays(1, &asset->VAO);

	glBindVertexArray(asset->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, asset->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * asset->nb_vertices * 3, asset->vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, asset->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * asset->nb_indices, asset->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	//Add if more

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

t_asset	*asset_create(const char *path_obj)
{
	t_asset		*asset;

	if (!(asset = ft_memalloc(sizeof(t_asset))))
		return (NULL);
	asset->type_draw = GL_TRIANGLES;
	if (!obj_pars(asset, path_obj))
	{
		ft_memdel((void *)&asset);
		return (NULL);
	}
	int i = 0;
	while (i < asset->nb_vertices * 3)
	{
		printf("v %f %f %f\n", asset->vertices[i], asset->vertices[i + 1], asset->vertices[i + 2]);
		i += 3;
	}
	i = 0;
	while (i < asset->nb_faces)
	{
		printf("f %i %i %i\n", asset->indices[i*3+0], asset->indices[i*3+1], asset->indices[i*3+2]);
		i++;
	}
	printf("%d\n", asset->nb_vertices);
	printf("%d\n", asset->nb_indices);
	printf("%d\n", asset->nb_faces);
	asset_buffers(asset);
	if (!asset_texture(asset, "img/prevo.img"))
	{
		ft_memdel((void *)&asset);
		return (NULL);
	}
	return (asset);
}

t_model	*model_create(const char *obj_path,
						const char *shader_vert_path,
						const char *shader_frag_path)
{
	t_model		*model;

	if (!(model = ft_memalloc(sizeof(t_model))))
		return (NULL);
	if (!(model->asset = asset_create(obj_path)))
		return (NULL);
	if (!shader_construct(&model->asset->shader, shader_vert_path, shader_frag_path))
		return (NULL);
	model->transform = matrix_get_identity();
	model->render = &model_render;
	return (model);
}

bool	render_loop(t_env *e, const char **argv, t_glfw *glfw)
{
	glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw->window, &event_mouse);

	t_model *teapot;

	if (!(teapot = model_create(argv[1],
							"shader/basic.vert",
							"shader/basic.frag")))
		return (end_of_program(e, "Erreur lors de la création de l'objet", 0));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

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

		view = matrix_view(&e->cam);

		teapot->render(teapot, &view, &projection);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
	return (true);
}
