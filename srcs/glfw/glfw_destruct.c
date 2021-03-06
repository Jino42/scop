/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_destruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 21:55:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/24 00:30:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_glfw.h"
#include <stdlib.h>

void			*glfw_destruct(t_glfw **glfw)
{
	glfwTerminate();
	if (glfw && *glfw)
	{
		if ((*glfw)->nk)
			nk_destruct(&(*glfw)->nk);
		ft_memdel((void **)glfw);
	}
	return (NULL);
}
