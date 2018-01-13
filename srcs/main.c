/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/13 23:03:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			main(int argc, char **argv)
{
	t_env	e;
	int		index;

	bzero(&e, sizeof(t_env));
	index = flag(&e.flag, argc, argv);
	e.cam.up = vector_construct(0, 1, 0);
	e.cam.to = vector_construct(0, 0, 1);
	e.cam.position = vector_construct(0, 0, -3);
	if (!glfw_init(&e.glfw))
		return (end_of_program(&e, "Error: Init glfw", 0));
	render_loop(&e, &e.glfw);
	end_of_program(&e, NULL, 0);
	return (0);
}
