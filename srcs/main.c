/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/09 21:19:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			main(int argc, char **argv)
{
	t_env	e;
	int		index;

	ft_bzero(&e, sizeof(t_env));
	index = flag(&e.flag, argc, argv);
	if (!glfw_init(&e.glfw))
		return (end_of_program(&e, "Error: Init glfw", 0));
	render_loop(&e, &e.glfw);
	end_of_program(&e, NULL, 0);
	return (0);
}
