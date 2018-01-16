/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/16 22:56:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//VertexsBufferObject : Vertex, Coordonates, Textures, -> RAM
//VertexArrayObject : tableau de reference of VBO
//ElementBufferObject :


float pitch = 0.f;
float yaw = -90.f;
t_vector front;



void event_mouse(GLFWwindow *window, double pos_x, double pos_y)
{
	(void)window;
	float sensitivity = 0.05;
	static bool first_callback = true;
	static float last_x = WIDTH/2, last_y = HEIGHT/2;

	if (first_callback)
	{
		last_x = pos_x;
		last_y = pos_y;
		first_callback = false;
	}

	float offset_x = (pos_x - last_x);
	float offset_y = (last_y - pos_y);
	last_x = pos_x;
	last_y = pos_y;

	offset_x *= sensitivity;
	offset_y *= sensitivity;

	yaw   += offset_x;
	pitch += offset_y;
	front.x = cosf(get_radians(pitch)) * cosf(get_radians(yaw));
	front.y = sinf(get_radians(pitch));
	front.z = sinf(get_radians(yaw));
	vector_normalize(&front);
}


bool	obj_pars(t_asset *asset, const char * path_obj)
{
	int		fd;
	char	*line;
	char	type[10];
	float	tab[4];
	int	tabi[4];

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (false);
	line = NULL;
	for (int i = 0; i < 0; i++)
		get_next_line(fd, &line);
	asset->vertices = ft_memalloc(sizeof(GLfloat) * 10000000);
	asset->indices = ft_memalloc(sizeof(GLuint) * 10000000);
	int i = 0;
	int j = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (sscanf(line, "%s ", type) != 1)
			return (true);
		if (!strcmp("v", type))
		{
			if (sscanf(line, "%s %f %f %f\n", type, &tab[0], &tab[1], &tab[2]) != 4)
				return (true);
			asset->vertices[3 * i + 0] = tab[0];
			asset->vertices[3 * i + 1] = tab[1];
			asset->vertices[3 * i + 2] = tab[2];
			asset->nb_vertices++;
		}
		else if (!strcmp("f", type))
		{
			int ret = 0;
			ret = sscanf(line, "%s %i %i %i\n", type, &tabi[0], &tabi[1], &tabi[2]);
			asset->indices[j] = tabi[0];
			j++;
			asset->indices[j] = tabi[1];
			j++;
			asset->indices[j] = tabi[2];
			asset->nb_truck += 3;
			asset->nb_faces += 1;
			j++;
		}
		i++;
	}
	return (true);
}

t_asset	*asset_create(const char *path_obj)
{
	t_asset		*asset;

	if (!(asset = ft_memalloc(sizeof(t_asset))))
		return (NULL);
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
	printf("%d\n", asset->nb_truck);
	printf("%d\n", asset->nb_faces);
	return (asset);
}

bool	pers_load(t_env *e, t_model **teapot)
{
	t_shader *shader;

	if (!(shader = ft_memalloc(sizeof(t_shader))))
		return (end_of_program(e, "Error Malloc", 0));
	if (!(*teapot = ft_memalloc(sizeof(t_model))))
		return (end_of_program(e, "Error Malloc", 0));
	if (!shader_construct(shader, "shader/basic.vert", "shader/basic.frag"))
		return (end_of_program(e, NULL, 0));
	if (!((*teapot)->asset = asset_create("ressources/teapot.obj")))
		return (end_of_program(e, "Create obj failed", 0));
	(*teapot)->asset->shader = shader;

	return (true);
}

void	render_loop(t_env *e, t_glfw *glfw)
{
	glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw->window, &event_mouse);

	t_model *teapot;

	if (!pers_load(e, &teapot))
		return ;

//		Buffer Management
///////////////////////////////////
	glGenBuffers(1, &teapot->asset->EBO);
	glGenBuffers(1, &teapot->asset->VBO);
	glGenVertexArrays(1, &teapot->asset->VAO);

	glBindVertexArray(teapot->asset->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, teapot->asset->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * teapot->asset->nb_vertices * 3, teapot->asset->vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, teapot->asset->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * teapot->asset->nb_truck, teapot->asset->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	//UnBind
	glBindVertexArray(0);				//UnBind
	///////////////////////////////////////////////

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	t_matrix model, view, projection;
	while (!glfwWindowShouldClose(glfw->window))
	{
		update_fps(&e->fps);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfw_input(glfw);
		event_cam(e, &e->cam, &e->glfw);

		e->cam.to = front;
		t_vector dir_look = vector_get_add(&e->cam.position, &e->cam.to);
		view = look_at(&e->cam.position, &dir_look, &e->cam.up);

		projection = matrix_get_projection_opengl(66.f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);

		teapot->asset->shader->use(teapot->asset->shader);

		glUniformMatrix4fv(
				glGetUniformLocation(teapot->asset->shader->program, "V"),
				1, GL_FALSE, &view.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(teapot->asset->shader->program, "P"),
				1, GL_FALSE, &projection.matrix[0][0]);
		model = matrix_get_identity();
		glUniformMatrix4fv(
				glGetUniformLocation(teapot->asset->shader->program, "M"),
				1, GL_FALSE, &model.matrix[0][0]);

		glBindVertexArray(teapot->asset->VAO);
		//glDrawArrays(GL_TRIANGLES, 0, teapot->asset->nb_vertices);
		glDrawElements(GL_TRIANGLES, teapot->asset->nb_truck, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
}
