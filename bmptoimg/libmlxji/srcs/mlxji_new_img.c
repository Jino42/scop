/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxji_new_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:35:28 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/08 02:26:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlxji.h"

t_img	*mlxji_new_img(void *mlx, int width, int height)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		exit(0);
	if (img == NULL)
		return (NULL);
	img->img = mlx_new_image(mlx, width, height);
	img->height = height;
	img->width = width;
	img->data = mlx_get_data_addr(img->img, &(img->bpp),
			&(img->size_line), &(img->endian));
	return (img);
}
