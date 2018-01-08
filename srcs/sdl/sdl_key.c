/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:39:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 21:54:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_sdl.h"

bool		sdl_key(t_sdl *sdl, const uint32_t key)
{
	if (sdl->event.key[key])
		return (true);
	return (false);
}
