/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/13 21:50:55 by ntoniolo         ###   ########.fr       */
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

void	render_loop(t_env *e, t_glfw *glfw)
{

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	ft_printf("Maximum number of vertex attribute GLSL supported : %i\n", (int)nrAttributes);

	GLfloat vertices[] = {
	    -0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
	     0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
	     -0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
		 0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		 0.90f, 0.90f, 0.0f,	0.0f, 0.0f, 0.0f,
		 0.85f, 0.90f, 0.0f,	0.0f, 0.90f, 0.0f,
		 0.90f, 0.70f, 0.0f,	0.0f, 0.70f, 0.0f
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
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	//Use strict === verif_ret

	t_matrix model, view, projection, mvp;
	t_vector vec;

	vec = vector_construct(0.0f, 0.0f, -3.0f);
	while (!glfwWindowShouldClose(glfw->window))
	{
		update_fps(&e->fps);
		glClear(GL_COLOR_BUFFER_BIT);
		glfw_input(glfw);

		//Tu peux mettre de uniform a l'infinie sans forcement les update cash
		//Update seulement ares UseProgram(yourShader);

/* 		// IF Uniform isnt used, then delete
		if (vertexColorLocation == -1)
		{
			end_of_program(e, "Error Opngel: glGetUniformLocation fail", 0);
			return ;
		}
*/
		view = matrix_get_translation(&vec);
		view = matrix_get_transpose(&view);
		model = matrix_get_rotation_y(glfwGetTime());
		model = matrix_get_transpose(&model);
		projection = matrix_get_projection_opengl(90.f, (float)WIDTH / (float)HEIGHT, 0.001f, 100.f);

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
						glGetUniformLocation(shader->program, "M"),
						1, GL_FALSE, &model.matrix[0][0]);
						glUniformMatrix4fv(
								glGetUniformLocation(shader->program, "V"),
								1, GL_FALSE, &view.matrix[0][0]);
								glUniformMatrix4fv(
										glGetUniformLocation(shader->program, "P"),
										1, GL_FALSE, &projection.matrix[0][0]);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
}
