/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxji_draw_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:00:00 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 18:00:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlxji.h"

void		mlxji_draw_case(t_img *img, t_pxtopx *px, int col)
{
	int x;
	int y;
	int dir_y;
	int dir_x;

	px->y1 < px->y2 ? (dir_y = 1) :
		(dir_y = -1);
	px->x1 < px->x2 ? (dir_x = 1) :
		(dir_x = -1);
	y = px->y1;
	while (y != px->y2)
	{
		x = px->x1;
		while (x != px->x2)
		{
			mlxji_put_pixel(img, x, y, col);
			x += dir_x;
		}
		y += dir_y;
	}
}
