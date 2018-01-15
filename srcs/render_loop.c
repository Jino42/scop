/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/15 20:38:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

//VertexsBufferObject : Vertex, Coordonates, Textures, -> RAM
//VertexArrayObject : tableau de reference of VBO
//ElementBufferObject :


float pitch = 0.f;
float yaw = -90.f;
t_vector front;

float get_radians(const float degrees)
{
	return ((degrees * M_PI) / 180.f);
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
	vector_normalize(&xaxis);
    t_vector yaxis = vector_get_cross_product(&zaxis, &xaxis);
	t_matrix rotation = matrix_get_identity();
    t_matrix translation = matrix_get_identity();

    rotation.matrix[0][0] = xaxis.x;
    rotation.matrix[1][0] = xaxis.y;
    rotation.matrix[2][0] = xaxis.z;
    rotation.matrix[0][1] = yaxis.x;
    rotation.matrix[1][1] = yaxis.y;
    rotation.matrix[2][1] = yaxis.z;
    rotation.matrix[0][2] = zaxis.x;
    rotation.matrix[1][2] = zaxis.y;
    rotation.matrix[2][2] = zaxis.z;

    translation.matrix[3][0] = position->x;
    translation.matrix[3][1] = position->y;
	translation.matrix[3][2] = position->z;

    return matrix_get_mult_matrix(&translation, &rotation);
}

void		update_cam(t_env *e, t_cam *cam, t_glfw *glfw)
{
	t_vector	dir;
	float		speed;

	speed = 2 * e->fps.delta_time;
	if (glfwGetKey(glfw->window, GLFW_KEY_UP) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		dir = vector_get_mult(&cam->to, -speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_DOWN) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		dir = vector_get_mult(&cam->to, speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_LEFT) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		dir = vector_get_cross_product(&e->cam.to, &e->cam.up);
		dir = vector_get_mult(&dir, speed);
		vector_add(&cam->position, &dir);
	}
	if (glfwGetKey(glfw->window, GLFW_KEY_RIGHT) == GLFW_PRESS
			|| glfwGetKey(glfw->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		dir = vector_get_cross_product(&e->cam.to, &e->cam.up);
		dir = vector_get_mult(&dir, -speed);
		vector_add(&cam->position, &dir);
	}
}

void mouse_callback(GLFWwindow *window, double pos_x, double pos_y)
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

void 	matrix_print(t_matrix *m, char *str)
{
	printf("Print %s :\n", str);
	int y = 0;
	int x;

	while (y < 4)
	{
		x = 0;
		printf("[");
		while(x < 4)
		{
			printf("%.2f ", m->matrix[y][x]);
			x++;
		}
		printf("]\n");
		y++;
	}
}

void	render_loop(t_env *e, t_glfw *glfw)
{

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	ft_printf("Maximum number of vertex attribute GLSL supported : %i\n", (int)nrAttributes);
	glfwSetInputMode(glfw->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw->window, &mouse_callback);

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

	float vertices2[] = {
		0.232406, -1.216630, 1.133818,
		0.232406, -0.745504, 2.843098,
		-0.227475, -0.745504, 2.843098,
		-0.227475, -1.216630, 1.133818,
		0.232407, 1.119982, 1.133819,
		0.232406, 1.119982, 1.602814,
		-0.227475, 1.119982, 1.602813,
		-0.227475, 1.119982, 1.133818,
		0.232406, -0.340316, 2.843098,
		-0.227475, -0.340316, 2.843098,
		0.232407, -0.305193, 1.133819,
		0.232407, -0.294496, 2.297937,
		-0.227475, -0.305193, 1.133818,
		-0.227475, -0.294496, 2.297937,
		0.232406, -1.222569, 1.497195,
		0.232406, -0.745504, 1.477731,
		-0.227475, -0.745504, 1.477731,
		-0.227475, -1.222569, 1.497194,
		-0.227403, -0.731178, 0.901477,
		-0.227403, -0.731178, -0.037620,
		0.223704, -0.731178, -0.037620,
		0.223704, -0.731178, 0.901477,
		-0.227403, 1.119377, 0.901477,
		-0.227403, 1.119377, -0.037620,
		0.223704, 1.119377, -0.037620,
		0.223704, 1.119377, 0.901477,
		-0.227403, -0.129772, 0.901477,
		-0.227403, 0.551492, 0.384487,
		-0.227403, 1.104268, 0.408501,
		-0.227403, 0.507336, 0.901477,
		0.223704, 0.507336, 0.901477,
		0.223704, 1.104269, 0.408501,
		0.223704, 0.551492, 0.384487,
		0.223704, -0.129772, 0.901477,
		-0.227403, 0.634134, -0.037620,
		-0.227403, -0.066768, 0.398575,
		-0.227403, -0.684649, 0.389681,
		-0.227403, -0.075523, -0.037620,
		0.223704, 0.634134, -0.037620,
		0.223704, -0.066768, 0.398575,
		0.223704, -0.684649, 0.389681,
		0.223704, -0.075523, -0.037620
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
	GLuint VBO, VAO, EBO, VBO2, VAO2;
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

	glGenBuffers(1, &VBO2);
	glGenVertexArrays(1, &VAO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);

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
		model = matrix_get_identity();
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "M"),
				1, GL_FALSE, &model.matrix[0][0]);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 41 * 3);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
}
