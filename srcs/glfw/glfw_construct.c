/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_construct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 21:49:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 21:55:07 by ntoniolo         ###   ########.fr       */
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

t_glfw		*glfw_construct(char *name, int width, int height)
{
	t_glfw	*glfw;

	if (!(glfw = ft_memalloc(sizeof(t_glfw))))
		return (NULL);
	bzero(glfw, sizeof(t_glfw));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfw->window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (glfw->window == NULL)
		return (glfw_destruct(&glfw));
	glfwMakeContextCurrent(glfw->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (glfw_destruct(&glfw));
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glfwSwapInterval(0);
	glfw->key = g_key;
	glfwSetCursorPosCallback(glfw->window, &event_mouse);
	glfwSetKeyCallback(glfw->window,
			(void(*)(GLFWwindow *, int, int, int, int))&glfw_key_callback);
	return (glfw);
}
