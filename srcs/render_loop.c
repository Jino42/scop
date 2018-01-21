/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/21 19:39:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//VertexsBufferObject : Vertex, Coordonates, Textures, -> RAM
//VertexArrayObject : tableau de reference of VBO
//ElementBufferObject :

void		model_render(t_model *model, t_matrix *view, t_matrix *projection)
{
	t_asset *asset;
	t_matrix temp, mvp;

	asset = model->asset;
	asset->shader.use(&asset->shader);
	model->transform.matrix[0][0] = 0.005;
	model->transform.matrix[1][1] = 0.005;
	model->transform.matrix[2][2] = 0.005;
	temp = matrix_get_mult_matrix(&model->transform, view);
	mvp = matrix_get_mult_matrix(&temp, projection);
	glUniformMatrix4fv(
			glGetUniformLocation(asset->shader.program, "MVP"),
			1, GL_FALSE, &mvp.matrix[0][0]);

	glBindVertexArray(asset->VAO);
	glDrawElements(GL_TRIANGLES, asset->nb_indices, GL_UNSIGNED_SHORT, 0);
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
	/*
	int i = 0;
	while (i < asset->nb_indices)
	{
		printf("%hi\n", asset->indices[i]);
		printf("%.2f %.2f %.2f\n", asset->indexed_v[i*3], asset->indexed_v[i*3+1], asset->indexed_v[i*3+2]);
		i++;
	}*/
	glGenBuffers(1, &asset->EBO);
	glGenVertexArrays(1, &asset->VAO);

	glBindVertexArray(asset->VAO);

	if (asset->flag & SCOP_V)
	{
		ft_printf("Set buffer : V\n");
		glGenBuffers(1, &asset->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, asset->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (asset->nb_indices) * 3, asset->indexed_v, GL_STATIC_DRAW);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (asset->flag & SCOP_VN)
	{
		ft_printf("Set buffer : VN\n");
		glGenBuffers(1, &asset->VNBO);
		glBindBuffer(GL_ARRAY_BUFFER, asset->VNBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (asset->nb_indices) * 3, asset->indexed_vn, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (asset->flag & SCOP_VT)
	{
		ft_printf("Set buffer : VT\n");
		glGenBuffers(1, &asset->VTBO);
		glBindBuffer(GL_ARRAY_BUFFER, asset->VTBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (asset->nb_indices) * 2, asset->indexed_vt, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, asset->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * asset->nb_indices, asset->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

t_asset	*asset_create(const char *path_obj)
{
	t_asset		*asset;

	if (!(asset = ft_memalloc(sizeof(t_asset))))
		return (NULL);
	asset->type_draw = GL_POINTS;
	if (!obj_pars(asset, path_obj))
	{
		ft_memdel((void *)&asset);
		return (NULL);
	}
	if (DEBUG)
	{
		int fd = open("osef", O_RDWR | O_TRUNC);
		int i = 0;
		dprintf(fd, "cc");
		while (i < asset->nb_v)
		{
			dprintf(fd, "v %f %f %f\n", asset->v[i * 3], asset->v[i * 3 + 1], asset->v[i * 3 + 2]);
			i++;
		}
		i = 0;
		while (i < asset->nb_vt)
		{
			dprintf(fd, "vt %f %f\n", asset->vt[i * 2], asset->vt[i * 2 + 1]);
			i++;
		}
		i = 0;
		while (i < asset->nb_vn)
		{
			dprintf(fd, "vn %f %f %f\n", asset->vn[i * 3], asset->vn[i * 3 + 1], asset->vn[i * 3 + 2]);
			i++;
		}
		i = 0;
		while (i < asset->nb_indices)
		{
			dprintf(fd, "v %f %f %f\n",
			asset->indexed_v[i],
			asset->indexed_v[i+1],
			asset->indexed_v[i+2]);
			i+=3;
		}
		dprintf(fd, "%d\n", asset->nb_v);
		dprintf(fd, "%d\n", asset->nb_indices);
		dprintf(fd, "%d\n", asset->nb_faces);
	}
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
