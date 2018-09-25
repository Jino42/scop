/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_construct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 21:49:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 20:21:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <strings.h>

bool		g_key[500];

void		glfw_key_callback(GLFWwindow *window, int inkey,
								int scancode, int action)
{
	if (action == GLFW_PRESS)
	{
		if (g_key[inkey])
			g_key[inkey] = false;
		else if (!g_key[inkey])
			g_key[inkey] = true;
		else
		{
			(void)window;
			(void)scancode;
		}
	}
}

static void	glfw_construct_set_opengl(void)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

t_glfw		*glfw_construct(char *name, int width, int height)
{
	t_glfw	*glfw;

	if (!(glfw = ft_memalloc(sizeof(t_glfw))))
		return (NULL);
	if (!glfwInit())
		return (glfw_destruct(&glfw));
	glfw_construct_set_opengl();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfw->window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (glfw->window == NULL)
		return (glfw_destruct(&glfw));
	glfwMakeContextCurrent(glfw->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (glfw_destruct(&glfw));
	glViewport(0, 0, WIDTH, HEIGHT);
	if (!(glfw->nk = nk_construct(glfw->window)))
		return (glfw_destruct(&glfw));
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glfwSwapInterval(0);
	glfw->key = g_key;
	glfwSetCursorPosCallback(glfw->window, &event_mouse);
	glfwSetKeyCallback(glfw->window,
			(void(*)(GLFWwindow *, int, int, int, int))&glfw_key_callback);
	return (glfw);
}
