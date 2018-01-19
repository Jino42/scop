/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxji_put_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:24:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/21 19:28:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlxji.h"

/*
** 1 Octet per pixel
** 1 B 2 G 3 R
*/

void	mlxji_put_pixel(t_img *img, int x, int y, int col)
{
	*((int*)&img->data[(x << 2) + (y * img->size_line)]) = col;
}
