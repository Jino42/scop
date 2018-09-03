/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_glfw.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 22:54:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/03 18:56:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_GLFW_H
# define SCOP_GLFW_H

#include "glfw3.h"
# include <stdbool.h>
# include "glad.h"

typedef struct		s_glfw
{
	GLFWwindow		*window;
	bool			*key;
}					t_glfw;

t_glfw				*glfw_construct(char *name, int width, int height);
void				*glfw_destruct(t_glfw **glfw);
void				glfw_callback_resize(GLFWwindow* window, int width, int height);
void				glfw_update(t_glfw *glfw);

#endif
