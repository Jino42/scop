/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:34:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 21:54:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_sdl.h"

bool		sdl_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (false);
	sdl->height = HEIGHT;
	sdl->width = WIDTH;
	sdl->ratio = (float)sdl->width / (float)sdl->height;
	if (!(sdl->win = SDL_CreateWindow("rt", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, sdl->width, sdl->height, SDL_WINDOW_SHOWN)))
		return (false);
	if (!(sdl->render = SDL_CreateRenderer(sdl->win, -1,
										SDL_RENDERER_ACCELERATED)))
		return (false);
	if (!(sdl->img = SDL_CreateTexture(sdl->render,
					SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
					sdl->width, sdl->height)))
		return (false);
	if (!(sdl->pix = ft_memalloc(sizeof(uint32_t) * sdl->width * sdl->height)))
		return (false);
	return (true);
}
