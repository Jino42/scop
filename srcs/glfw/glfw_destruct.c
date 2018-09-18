/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_destruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 21:55:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 21:55:31 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_glfw.h"
#include <stdlib.h>

void			*glfw_destruct(t_glfw **glfw)
{
	glfwTerminate();
	if (glfw && *glfw)
	{
		free(*glfw);
		*glfw = NULL;
	}
	return (NULL);
}
