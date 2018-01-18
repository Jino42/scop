/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/18 23:34:54 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			main(int argc, char **argv)
{
	t_env	e;
	int		index;

	bzero(&e, sizeof(t_env));
	index = flag(&e.flag, argc, argv);
	e.cam.up = vector_construct(0.f, 1.f, 0.f);
	e.cam.to = vector_construct(0.f, 0.f, 1.f);
	e.cam.position = vector_construct(0.f, -2.f, -6.f);
	if (!glfw_init(&e.glfw))
		return (end_of_program(&e, "Error: Init glfw", 0));
	render_loop(&e, (const char **)argv, &e.glfw);
	end_of_program(&e, NULL, 0);
	return (0);
}
