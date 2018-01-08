/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:51:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 21:54:00 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_sdl.h"

void	end_sdl(t_sdl *sdl)
{
	if (sdl->pix)
		ft_memdel((void *)&sdl->pix);
	if (sdl->img)
		SDL_DestroyTexture(sdl->img);
	if (sdl->render)
		SDL_DestroyRenderer(sdl->render);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}
