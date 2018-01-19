/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxji_draw_x_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:01:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 18:04:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlxji.h"

void		mlxji_draw_x_line(t_img *img, t_pxtopx *to, int col)
{
	int y;

	y = to->y1 * img->size_line;
	while (to->x1 < to->x2)
	{
		*((int *)&img->data[(to->x1 << 2) + y]) = col;
		to->x1++;
	}
}
