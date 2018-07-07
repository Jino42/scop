/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/08 00:31:12 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "scop_glfw.h"
# include "libft.h"
# include "matrix.h"
# include "material.h"

# include <math.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdio.h>
#include <stdlib.h>

# define DEBUG 1

# define BUFFER_OBJ (2048)

# define WIDTH 1920
# define HEIGHT 1080

# define SCOP_V (1 << 1)
# define SCOP_VT (1 << 2)
# define SCOP_VN (1 << 3)
# define F_TEXTURE (1 << 4)

#define MAX_SOURCE_SIZE 8000
#define BUFFER_LOG 2048



typedef struct		s_fps
{
	struct timeval	step2;
	struct timeval	step;
	struct timeval	cur;
	float			delta_time;
	unsigned int	fps;
	unsigned int	ret_fps;
}					t_fps;
t_fps 				*fps_construct();
void 				*fps_destruct(t_fps **e);
void				fps_update(t_fps *fps, float *ptr);

typedef struct		s_env
{
	t_fps			*fps;
	t_glfw			*glfw;

	int64_t			flag;
}					t_env;
t_env 				*env_construct();
void 				*env_destruct(void *ptr);

int					flag(int64_t *f, int argc, char **argv);
int					end_of_program(t_env *e, char *str, int flag);



//t_event_camfps		*singleton_mouse();
void				event_mouse(GLFWwindow *window, double pos_x, double pos_y);
//void				event_cam(t_env *e, t_cam *cam, t_glfw *glfw);

float				get_degrees(const float radians);
float				get_radians(const float degrees);

t_matrix		look_at(const t_vector *position,
						const t_vector *to,
						const t_vector *up);
t_matrix		matrix_get_projection_opengl(const float fov,
												const float ratio,
												const float near,
												const float far);

#endif
