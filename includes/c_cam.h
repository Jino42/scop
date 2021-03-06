/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_cam.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:41:49 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 17:55:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_CAM_H
# define C_CAM_H

# include "matrix.h"
# include <stdint.h>

typedef struct		s_cam
{
	bool			fps;
	bool			first_callback;
	float			fov;
	float			near;
	float			far;
	float			pitch;
	float			yaw;
	float			sensitivity;
	t_vector		front;
	t_vector		last_cursor_position;
	t_vector		position;
	t_vector		to;
	t_vector		up;
	t_matrix		view;
	t_matrix		projection;
	int				flag;
}					t_cam;
t_cam				*cam_construct();
void				*cam_destruct(t_cam **cam);
t_vector			cam_get_front(float pitch, float yaw);

#endif
