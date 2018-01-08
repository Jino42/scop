/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:32:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 21:52:12 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	env_end(t_env *e)
{
	(void)e;
}

int			end_of_program(t_env *e, char *str, int flag)
{
	if (str)
		ft_dprintf(2, "%s\n", str);
	if (flag)
		ft_dprintf(2, "%s\n", SDL_GetError());
	env_end(e);
	end_sdl(&e->sdl);
	return (0);
}
