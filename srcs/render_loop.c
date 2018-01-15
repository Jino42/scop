/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/15 23:42:35 by ntoniolo         ###   ########.fr       */
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
	float	tab[3];

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (false);
	line = NULL;
	for (int i = 0; i < 4; i++)
		get_next_line(fd, &line);
	asset->vertices = ft_memalloc(sizeof(GLfloat) * 10000000);
	int i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (sscanf(line, "%s %f %f %f\n", type, &tab[0], &tab[1], &tab[2]) != 4)
			return (true);
		printf("%s %f %f %f\n", type, tab[0], tab[1], tab[2]);
		asset->vertices[3 * i + 0] = tab[0];
		asset->vertices[3 * i + 1] = tab[1];
		asset->vertices[3 * i + 2] = tab[2];
		asset->nb_vertices += 3;
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
	while (i < asset->nb_vertices)
	{
		printf("%10.5f ", asset->vertices[i]);
		printf("%10.5f ", asset->vertices[i + 1]);
		printf("%10.5f ", asset->vertices[i + 2]);
		printf("\n");
		i += 3;
	}
	return (asset);
}

void	render_loop(t_env *e, t_glfw *glfw)
{
	glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw->window, &event_mouse);
	float vertices[] = {
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f
	};
	GLuint indices[] = {
		0, 1, 2,
		1, 2, 3,
		4, 5, 6
	};

	t_model *teapot;
	t_shader *shader;
	if (!(shader = ft_memalloc(sizeof(t_shader))))
	{
		end_of_program(e, "Error Malloc", 0);
		return ;
	}
	if (!(teapot = ft_memalloc(sizeof(t_model))))
	{
		end_of_program(e, "Error Malloc", 0);
		return ;
	}
	if (!shader_construct(shader, "shader/basic.vert", "shader/basic.frag"))
	{
		end_of_program(e, NULL, 0);
		return ;
	}
	if (!(teapot->asset = asset_create("ressources/42.obj")))
	{
		end_of_program(e, "Create obj failed", 0);
		return ;
	}
	teapot->asset->shader = shader;

//		Buffer Management
///////////////////////////////////
	float place[] = {
		 0.0f,  0.0f,  0.0f,
		 2.0f,  5.0f, -15.0f,
		-1.5f, -2.2f, -2.5f,
		-3.8f, -2.0f, -12.3f,
		2.4f, -0.4f, -3.5f,
		-1.7f,  3.0f, -7.5f,
		 1.3f, -2.0f, -2.5f,
		 1.5f,  2.0f, -2.5f,
		 1.5f,  0.2f, -1.5f,
		-1.3f,  1.0f, -1.5f
	};
	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	//UnBind
	glBindVertexArray(0);				//UnBind
	///////////////////////////////////////////

	glGenBuffers(1, &teapot->asset->VBO);
	glGenVertexArrays(1, &teapot->asset->VAO);

	glBindVertexArray(teapot->asset->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, teapot->asset->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), teapot->asset->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	//UnBind
	glBindVertexArray(0);				//UnBind
	///////////////////////////////////////////////

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	//Use strict === verif_ret

	t_matrix model, view, projection, mvp, temp;
	(void)temp;
	while (!glfwWindowShouldClose(glfw->window))
	{
		update_fps(&e->fps);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfw_input(glfw);
		event_cam(e, &e->cam, &e->glfw);

		//Tu peux mettre de uniform a l'infinie sans forcement les update cash
		//Update seulement ares UseProgram(yourShader);

/* 		// IF Uniform isnt used, then delete
		if (vertexColorLocation == -1)
		{
			end_of_program(e, "Error Opngel: glGetUniformLocation fail", 0);
			return ;
		}
*/
		e->cam.to = front;
		t_vector dir_look = vector_get_add(&e->cam.position, &e->cam.to);
		view = look_at(&e->cam.position, &dir_look, &e->cam.up);


		projection = matrix_get_projection_opengl(66.f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);
		mvp = matrix_get_mult_matrix(&view, &projection);
		mvp = matrix_get_mult_matrix(&model, &mvp);

		greenValue += 0.001;
		shader->use(shader);
		glUniform4f(
				glGetUniformLocation(shader->program, "testUniform"),
				0.3f, greenValue, 0.45f, 1.0f);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "MVP"),
				1, GL_FALSE, &mvp.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "V"),
				1, GL_FALSE, &view.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "P"),
				1, GL_FALSE, &projection.matrix[0][0]);
		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		for (uint32_t i = 0; i < 10; i++)
		{
			t_vector pl = vector_construct(place[i*3], place[i*3+1], place[i*3+2]);
			model = matrix_get_translation(&pl);
			model = matrix_get_transpose(&model);
			glUniformMatrix4fv(
					glGetUniformLocation(shader->program, "M"),
					1, GL_FALSE, &model.matrix[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(teapot->asset->VAO);
		model = matrix_get_identity();
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "M"),
				1, GL_FALSE, &model.matrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, teapot->asset->nb_vertices);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
}
