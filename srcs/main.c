/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:40:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/28 00:02:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			main(int argc, char **argv)
{
	t_env *e;

	if (argc != 2)
	{
		dprintf(2, "usage: ./scop file.json\n");
		return (0);
	}
	if (!(e = env_construct(argc, argv)))
	{
		return (ft_bool_error("Erreur: L'initialisation de t_env a échoué",
					NULL, NULL));
	}
	loop(e);
	env_destruct(e);
	return (0);
}
