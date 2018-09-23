/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_fps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:28:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/23 18:12:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		*fps_destruct(t_fps **fps)
{
	ft_memdel((void **)fps);
	return (NULL);
}

t_fps		*fps_construct(void)
{
	t_fps *fps;

	if (!(fps = ft_memalloc(sizeof(t_fps))))
		return (NULL);
	return (fps);
}

int			fps_timestamp(t_fps *fps)
{
	return (fps->cur.tv_sec * 1000 + fps->cur.tv_usec / 1000);
}

void		fps_update(t_fps *fps, float *ptr)
{
	gettimeofday(&fps->step2, NULL);
	if (fps->fps)
	{
		fps->delta_time = (float)(fps->step2.tv_usec - fps->cur.tv_usec)
													/ 1000000;
		if (fps->delta_time < 0.005)
			fps->delta_time = 0.005;
		if (fps->cur.tv_sec != fps->step2.tv_sec)
			fps->delta_time = (float)(fps->step2.tv_usec +
								(1000000 - fps->cur.tv_usec)) / 1000000;
	}
	gettimeofday(&fps->cur, NULL);
	if (fps->cur.tv_sec - fps->step.tv_sec)
	{
		fps->ret_fps = fps->fps;
		ft_printf("FPS [%i]\n", fps->ret_fps);
		fps->fps = 0;
		gettimeofday(&fps->step, NULL);
	}
	fps->fps++;
	if (ptr)
		*ptr = fps->delta_time;
	fps->time += fps->delta_time;
}
