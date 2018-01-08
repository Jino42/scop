/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 21:52:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			main(int argc, char **argv)
{
	t_env	e;
	int		index;

	ft_bzero(&e, sizeof(t_env));
	index = flag(&e.flag, argc, argv);
	if (!sdl_init(&e.sdl))
		return (end_of_program(&e, "Erreur a l'initialisation de la SDL: ", ERROR_SDL));
	scop_loop(&e, &e.sdl);
	end_of_program(&e, NULL, 0);
	return (0);
}
