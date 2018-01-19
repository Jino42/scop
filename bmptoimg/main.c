/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 21:02:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/25 21:34:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlxji.h"
#include "mlx.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BMP_HEAD_TYPE 2
#define BMP_HEAD_FILE 12
#define BMP_HEAD 40
#define BMP_TYPE_BM 19778

typedef struct	s_bmp
{
	short	type;
	int		file_size;
	int 	private1;
	int		offset;
	int		info_reader_size;
	int		width;
	int		height;
	short	nb_plans;
	short	bpp;
	int		compression;
	int		size_img;
	int		x_pxpmeter;
	int		y_pxpmeter;
	int		color_use;
	int		color_important;
}				t_bmp;

void		read_bmp(t_bmp bmp, int fd, unsigned char *datas)
{
	unsigned char tab[3];
	int x;
	int y;
	int width_pixel;

	width_pixel = bmp.width * 4;
	y = bmp.height - 1;
	while (y >= 0)
	{
		x = bmp.width - 1;
		while (x >= 0)
		{
			read(fd, tab, 3);
			datas[x * 4 + y * width_pixel] = tab[0];
			datas[x * 4 + y * width_pixel + 1] = tab[1];
			datas[x * 4 + y * width_pixel + 2] = tab[2];
			x--;
		}
		if (bmp.width % 4)
			read(fd, tab, bmp.width % 4);
		y--;
	}
}

int			set_bmp(t_bmp *bmp, int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (!*fd)
		return (0);
	read(*fd, &bmp->type, BMP_HEAD_TYPE);
	read(*fd, &bmp->file_size, BMP_HEAD_FILE);
	read(*fd, &bmp->info_reader_size, BMP_HEAD);
	printf("%i %i %i\n", bmp->compression, bmp->bpp, bmp->type);
	if (bmp->compression || bmp->bpp != 24 || bmp->type != BMP_TYPE_BM)
		return (0);
	lseek(*fd, bmp->offset, SEEK_SET);
	return (1);
}

int			write_img(t_bmp *bmp, unsigned char *datas, char *file_out, size_t size)
{
	int	fd_out;

	fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC);
	if (!fd_out)
		return (ft_ret_error("Erreur sur le fichier de sortie\n"));
	write(fd_out, &bmp->width, sizeof(int));
	write(fd_out, &bmp->height, sizeof(int));
	ft_printf("W %i H %i\n", bmp->width, bmp->height);
	write(fd_out, datas, size);
	close(fd_out);
	return (1);
}

int			print_img(char **argv)
{
	int		fd;
	void	*mlx;
	t_img	*img;
	int		height;
	int		width;
	void *win;
	int x, y;
	unsigned char tab[4];

	fd = open(argv[2], O_RDONLY);
	if (!(fd))
		return (ft_ret_error("Fichier non conforme\n"));
	mlx = mlx_init();

	read(fd, &width, sizeof(int));
	read(fd, &height, sizeof(int));
	img = mlxji_new_img(mlx, width, height);
	win = mlx_new_window(mlx, width, height, "test img");

	ft_printf("Width : [%i] Height : [%i]\n", width, height);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			read(fd, tab, 4);
			img->data[x * 4 + y * img->size_line] = tab[0];
			img->data[x * 4 + y * img->size_line + 1] = tab[1];
			img->data[x * 4 + y * img->size_line + 2] = tab[2];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win, img->img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, win);
	mlx_destroy_window(mlx, img->img);
	return (1);
}

void		make_img(char **argv)
{
	int fd;
	unsigned char	*datas;
	t_bmp bmp;

	if (!(set_bmp(&bmp, &fd, argv[2])))
		exit(ft_ret_error(("Erreur sur le BMP !\n")));
	if (!(datas = ft_memalloc((bmp.height * bmp.width * 4))))
		exit(0);
	read_bmp(bmp, fd, datas);
	close(fd);
	write_img(&bmp, datas, argv[3], bmp.width * bmp.height * 4);
	free(datas);
}

int			main(int argc, char **argv)
{
	if (argv[1][0] == '1')
	{
		if (argc != 3)
			return (ft_ret_error("Nombre d'arguments incorrects"));
		print_img(argv);
	}
	else if (argv[1][0] == '2')
	{
		if (argc != 4)
			return (ft_ret_error("Nombre d'arguments incorrects"));
		make_img(argv);
	}
	else
		return (ft_ret_error("./convert_to_bmp [1 texture.img] [2 texture.png texture.img\n"));
	return (0);
}
