/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:56:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/21 22:29:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** incr :
**	_____________ _____________	_____________ _____________
**	|     | y2  | | y2  |     | | x 1 |     | |     | x-1 |
**	|     | x2  | | x2  |     | | y 1 |     | |     | y 1 |
**	|-----|-----| |-----|-----| |-----|-----| |-----|-----|
**	| x 1 |     | |     | x-1 |	|     | x2  | | x2  |     |
**	| y-1 |     | |     | y-1 | |     | y2  | | y2  |     |
**	------------- -------------	------------- -------------
**
**
**	if Dy > Dx							else Dx > Dy
**	y++ full;								x++ full;
**	cumul = dx;								cumul = dy;
**	if (cumul >= dy)						if (cumul >= dx)
**		cumul += dy;							cumul += dy;
*/

#include "../includes/mlxji.h"

static void	dx_dy(t_img *img, int col, t_line *line)
{
	line->cumul = 0;
	while (line->i < line->dx)
	{
		line->x += line->xincr;
		line->cumul += line->dy;
		if (line->cumul >= line->dx)
		{
			line->cumul -= line->dx;
			line->y += line->yincr;
		}
		if ((line->x >= 0 && line->x < img->width) &&
			(line->y >= 0 && line->y < img->height))
			mlxji_put_pixel(img, line->x, line->y, col);
		line->i++;
	}
}

static void	dy_dx(t_img *img, int col, t_line *line)
{
	line->cumul = 0;
	while (line->i < line->dy)
	{
		line->y += line->yincr;
		line->cumul += line->dx;
		if (line->cumul >= line->dy)
		{
			line->cumul -= line->dy;
			line->x += line->xincr;
		}
		if ((line->x >= 0 && line->x < img->width) &&
			(line->y >= 0 && line->y < img->height))
			mlxji_put_pixel(img, line->x, line->y, col);
		line->i++;
	}
}

int			mlxji_draw_line(t_img *img, t_pxtopx *to, int col)
{
	t_line	line;

	line.x = to->x1;
	line.y = to->y1;
	line.dx = to->x2 - to->x1;
	line.dy = to->y2 - to->y1;
	line.xincr = (line.dx > 0) ? 1 : -1;
	line.yincr = (line.dy > 0) ? 1 : -1;
	line.dx = abs(line.dx);
	line.dy = abs(line.dy);
	line.i = 0;
	if ((line.x >= 0 && line.x <= img->width) &&
		(line.y >= 0 && line.y <= img->height))
		mlxji_put_pixel(img, line.x, line.y, col);
	if (line.dx > line.dy)
		dx_dy(img, col, &line);
	else
		dy_dx(img, col, &line);
	return (1);
}
