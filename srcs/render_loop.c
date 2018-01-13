/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/13 18:22:13 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

//VertexsBufferObject : Vertex, Coordonates, Textures, -> RAM
//VertexArrayObject : tableau de reference of VBO
//ElementBufferObject :

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

	t_matrix matrix_test;
	t_matrix matrix_testy;
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
		matrix_testy = matrix_get_rotation_y(glfwGetTime());
		matrix_test = matrix_get_rotation_x(glfwGetTime());
		matrix_test = matrix_get_mult_matrix(&matrix_test, &matrix_testy);
		greenValue += 0.001;
		shader->use(shader);
		glUniform4f(
				glGetUniformLocation(shader->program, "testUniform"),
				0.3f, greenValue, 0.45f, 1.0f);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "transform"),
				1, GL_FALSE, &matrix_test.matrix[0][0]);
		glUniformMatrix4fv(
				glGetUniformLocation(shader->program, "transform"),
				1, GL_FALSE, &matrix_test.matrix[0][0]);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(glfw->window);
		glfwPollEvents();
	}
}
