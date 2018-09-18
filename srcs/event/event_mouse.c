/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:34:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 21:56:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vector			*singleton_mouse_position(void)
{
	static t_vector vector = {0.f, 0.f, 0.f, 0.f};

	return (&vector);
}

void				event_mouse(GLFWwindow *window, double pos_x, double pos_y)
{
	t_vector *vector;

	(void)window;
	vector = singleton_mouse_position();
	vector->x = pos_x;
	vector->y = pos_y;
}
