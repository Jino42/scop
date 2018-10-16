/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:40:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 18:42:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			main(int argc, char **argv)
{
	t_env *e;

	if (argc != 2 && argc != 3)
	{
		dprintf(2, "usage: ./scop file.json\n");
		return (0);
	}
	if (!(e = env_construct(argc, argv)))
	{
		return (ft_bool_error("Error: t_env cannot be initialised",
					NULL, NULL));
	}
	if (!e->debug)
		loop(e);
	env_destruct(e);
	return (0);
}
