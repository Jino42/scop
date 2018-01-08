/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:59:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 22:02:13 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	scop_loop(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		SDL_UpdateTexture(sdl->img, NULL, sdl->pix,
									sdl->width * sizeof(uint32_t));
		SDL_RenderCopy(sdl->render, sdl->img, NULL, NULL);
		SDL_RenderPresent(sdl->render);
		SDL_RenderClear(sdl->render);
	}
}
