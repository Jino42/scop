/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_sdl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:30:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 21:54:31 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_SDL_H
# define SCOP_SDL_H

# include "SDL.h"
# include "libft.h"

# include <stdbool.h>
# include <stdint.h>

# define HEIGHT 720
# define WIDTH 1280
# define SIZE_RENDER (HEIGHT * WIDTH * 4)

typedef struct		s_event
{
	bool			key[SDL_NUM_SCANCODES];
	bool			mouse[8];

	int				m_x;
	int				m_y;
	bool			exit;
}					t_event;

typedef struct		s_sdl
{
	uint32_t		width;
	uint32_t		height;
	float			ratio;
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Texture		*img;
	SDL_Event		ev;
	t_event			event;
	uint32_t		*pix;
}					t_sdl;

bool				sdl_init(t_sdl *sdl);
void				sdl_put_pixel(t_sdl *sdl, const uint32_t x,
							const uint32_t y, uint32_t const col);
void				sdl_update_event(t_sdl *sdl, t_event *event);
bool				sdl_event_exit(t_sdl *sdl);
bool				sdl_key(t_sdl *sdl, const uint32_t key);
void				end_sdl(t_sdl *sdl);

#endif
