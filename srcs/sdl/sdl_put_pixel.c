/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:34:37 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 21:54:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_sdl.h"

void				sdl_put_pixel(t_sdl *sdl, const uint32_t x,
						const uint32_t y, uint32_t const col)
{
	sdl->pix[x + y * sdl->width] = col;
}
