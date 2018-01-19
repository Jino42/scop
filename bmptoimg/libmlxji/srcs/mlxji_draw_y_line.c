/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxji_draw_y_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:00:41 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 18:00:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlxji.h"

void		mlxji_draw_y_line(t_img *img, t_pxtopx *to, int col)
{
	int x;

	x = to->x1 << 2;
	while (to->y1 < to->y2)
	{
		*((int *)&img->data[x + to->y1 * img->size_line]) = col;
		to->y1++;
	}
}
