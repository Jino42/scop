/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/13 23:08:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

//VertexsBufferObject : Vertex, Coordonates, Textures, -> RAM
//VertexArrayObject : tableau de reference of VBO
//ElementBufferObject :

t_matrix	matrix_get_transpose(t_matrix *mn)
{
	t_matrix	m;
	int			y;
	int			x;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			m.matrix[x][y] = mn->matrix[y][x];
			x++;
		}
		y++;
	}
	return (m);
}

float get_radians(const float degrees)
{
	return (degrees * M_PI / 180);
}
float get_degrees(const float radians)
{
	return (radians * 180 / M_PI);
}

t_matrix matrix_get_projection_opengl(const float angleOfView,
										const float imageAspectRatio,
										const float near,
										const float far)
{
	t_matrix m;
	float scale, r, t, b, l;

	scale = tanf(angleOfView * 0.5f * M_PI / 180.0f) * near;
	r = imageAspectRatio * scale;
	l = -r;
    t = scale;
	b = -t;

    m.matrix[0][0] = 2.f * near / (r - l);
    m.matrix[0][1] = 0.f;
    m.matrix[0][2] = 0.f;
    m.matrix[0][3] = 0.f;

    m.matrix[1][0] = 0.f;
    m.matrix[1][1] = 2.f * near / (t - b);
    m.matrix[1][2] = 0.f;
    m.matrix[1][3] = 0.f;

    m.matrix[2][0] = (r + l) / (r - l);
    m.matrix[2][1] = (t + b) / (t - b);
    m.matrix[2][2] = -(far + near) / (far - near);
    m.matrix[2][3] = -1.f;

    m.matrix[3][0] = 0;
    m.matrix[3][1] = 0;
    m.matrix[3][2] = -2.f * far * near / (far - near);
    m.matrix[3][3] = 0;
	return (m);
}

t_matrix look_at(t_vector *position, t_vector *to, t_vector *up)
{
	t_vector zaxis = vector_get_sub(position, to);
	vector_normalize(&zaxis);
	t_vector tmp = vector_get_normalize(up);
    t_vector xaxis = vector_get_cross_product(&tmp, &zaxis);
    t_vector yaxis = vector_get_cross_product(&zaxis, &xaxis);
	(void)yaxis;
    t_matrix cam_to_world = matrix_get_identity();
/*
    cam_to_world.matrix[0][0] = xaxis.x;
    cam_to_world.matrix[0][1] = xaxis.y;
    cam_to_world.matrix[0][2] = xaxis.z;
    cam_to_world.matrix[1][0] = yaxis.x;
    cam_to_world.matrix[1][1] = yaxis.y;
    cam_to_world.matrix[1][2] = yaxis.z;
    cam_to_world.matrix[2][0] = zaxis.x;
    cam_to_world.matrix[2][1] = zaxis.y;
    cam_to_world.matrix[2][2] = zaxis.z;
*/
    cam_to_world.matrix[3][0] = position->x;
    cam_to_world.matrix[3][1] = position->y;
    cam_to_world.matrix[3][2] = position->z;

    return cam_to_world;
}

void		update_cam(t_env *e, t_cam *cam, t_glfw *glfw)
{
	t_vector	dir;
	float		speed;

	speed = 2 * e->fps.delta_time;
	if (glfwGetKey(glfw->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		dir = vector_get_mult(&cam->to, speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		dir = vector_get_mult(&cam->to, -speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		dir = vector_get_cross_product(&e->cam.to, &e->cam.up);
		dir = vector_get_mult(&dir, speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		dir = vector_get_cross_product(&e->cam.to, &e->cam.up);
		dir = vector_get_mult(&dir, -speed);
		vector_add(&cam->position, &dir);
	}
}

void	render_loop(t_env *e, t_glfw *glfw)
{

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	ft_printf("Maximum number of vertex attribute GLSL supported : %i\n", (int)nrAttributes);

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

	t_shader *shader;
	if (!(shader = ft_memalloc(sizeof(t_shader))))
	{
		end_of_program(e, "Error Malloc", 0);
		return ;
	}
	if (!shader_construct(shader, "shader/basic.vert", "shader/basic.frag"))
	{
		end_of_program(e, NULL, 0);
		return ;
	}
//		Buffer Management
///////////////////////////////////
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
//////////////////////////////////////

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
		update_cam(e, &e->cam, &e->glfw);

		//Tu peux mettre de uniform a l'infinie sans forcement les update cash
		//Update seulement ares UseProgram(yourShader);

/* 		// IF Uniform isnt used, then delete
		if (vertexColorLocation == -1)
		{
			end_of_program(e, "Error Opngel: glGetUniformLocation fail", 0);
			return ;
		}
*/
		view = look_at(&e->cam.position, &e->cam.to, &e->cam.up);
		//view = matrix_get_transpose(&view);


		//model = matrix_get_rotation_y(glfwGetTime());
		//temp = matrix_get_rotation_x(glfwGetTime() / 2);
		//model = matrix_get_mult_matrix(&model, &temp);
		model = matrix_get_identity();
		model = matrix_get_transpose(&model);
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

		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
}
