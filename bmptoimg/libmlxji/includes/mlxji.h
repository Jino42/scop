/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxji.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:26:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/28 18:05:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXJI_H
# define MLXJI_H

# include "mlx.h"
# include <stdlib.h>
# include <string.h>

/*
** Input Event Masks. Used as event-mask window attribute and
** as argument to Grab requests.  Not to be confused with event names.
*/

# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)
# define BUTTONPRESSMASK (1L<<2)
# define BUTTONRELEASEMASK (1L<<3)
# define ENTERWINDOWMASK (1L<<4)
# define LEAVEWINDOWMASK (1L<<5)

/*
** Event names.  Used in "type" field in XEvent structures.  Not to be
** confused with event masks above.  They start from 2 because 0 and 1
** are reserved in the protocol for errors and replies.
*/

# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MOTIONNOTIFY 6
# define ENTERNOTIFY 7
# define LEAVENOTIFY 8
# define FOCUSIN 9
# define FOCUSOUT 10

typedef struct		s_img
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}					t_img;

typedef struct		s_px
{
	int			r;
	int			g;
	int			b;
}					t_px;

typedef struct		s_hsv
{
	double		rf;
	double		gf;
	double		bf;
	double		i;
	double		min;
	double		f;
	double		down;
	double		up;
}					t_hsv;

typedef struct		s_line
{
	int			dx;
	int			dy;
	int			x;
	int			y;
	int			xincr;
	int			yincr;
	int			cumul;
	int			i;
}					t_line;

typedef struct		s_pxtopx
{
	int			x1;
	int			x2;
	int			y1;
	int			y2;
}					t_pxtopx;

int					mlxji_clear_img(t_img *img);
int					mlxji_hsv_to_rgb(t_px *px, float h, float s, float v);
int					mlxji_draw_line(t_img *img, t_pxtopx *to, int col);
int					mlxji_rgb_to_int(t_px *col);
void				mlxji_put_pixel(t_img *img, int x, int y, int col);
void				mlxji_draw_case(t_img *img, t_pxtopx *px, int col);
void				mlxji_draw_y_line(t_img *img, t_pxtopx *to, int col);
void				mlxji_draw_x_line(t_img *img, t_pxtopx *to, int col);
t_img				*mlxji_new_img(void *mlx, int width, int height);

#endif
