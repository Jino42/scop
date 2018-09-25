/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load_tga.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 21:30:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 20:27:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool			tga_destruct_failed(t_tga *tga)
{
	if (tga)
		close(tga->fd);
	return (false);
}

bool			tga_destruct_success(t_tga *tga, t_texture *texture)
{
	if (tga)
	{
		if (texture)
		{
			texture->width = tga->width;
			texture->height = tga->height;
			texture->data = tga->data;
		}
		close(tga->fd);
	}
	return (true);
}

static void		texture_load_tga_reverse_bgr(t_tga *tga, long image_size)
{
	int				color_mode;
	unsigned char	color_swap;
	int				i;

	color_mode = tga->bit_count / 8;
	i = 0;
	while (i < image_size)
	{
		color_swap = tga->data[i];
		tga->data[i] = tga->data[i + 2];
		tga->data[i + 2] = color_swap;
		i += color_mode;
	}
}

static bool		texture_load_tga_read_data(t_tga *tga)
{
	read(tga->fd, &tga->buffer, sizeof(unsigned char) * 2);
	read(tga->fd, &tga->type_code, sizeof(unsigned char));
	if (tga->type_code != 2)
	{
		dprintf(0, "Fichier invalide\n");
		return (tga_destruct_failed(tga));
	}
	read(tga->fd, &tga->buffer, sizeof(short int) * 4 + sizeof(unsigned char));
	read(tga->fd, &tga->width, sizeof(short int));
	read(tga->fd, &tga->height, sizeof(short int));
	read(tga->fd, &tga->bit_count, sizeof(unsigned char));
	read(tga->fd, &tga->buffer, sizeof(unsigned char));
	return (true);
}

bool			texture_load_tga(t_texture *texture, const char *filename)
{
	t_tga			tga;
	long			image_size;
	int				color_mode;

	tga.fd = open(filename, O_RDONLY);
	if (tga.fd <= 0)
	{
		dprintf(0, "Chemin ou fichier invalide\n");
		return (tga_destruct_failed(&tga));
	}
	texture_load_tga_read_data(&tga);
	color_mode = tga.bit_count / 8;
	image_size = tga.width * tga.height * color_mode;
	if (!(tga.data = (unsigned char*)ft_memalloc(
			sizeof(unsigned char) * image_size)))
		return (tga_destruct_failed(&tga));
	read(tga.fd, tga.data, sizeof(unsigned char) * image_size);
	texture_load_tga_reverse_bgr(&tga, image_size);
	return (tga_destruct_success(&tga, texture));
}
