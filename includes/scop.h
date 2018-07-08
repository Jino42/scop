/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/08 21:19:50 by ntoniolo         ###   ########.fr       */
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


/*						*/
/*		  SHADER		*/
/*						*/
typedef struct		s_shader
{
	GLuint			program;

	void			(*use)(struct s_shader *);
}					t_shader;
void				*shader_destroy(t_shader **shader);
t_shader			*shader_construct(const char *vertex_shader_path,
									const char *fragment_shader_path);

typedef struct		s_m_shader
{
	unsigned int	size;
	t_shader		**shader;
	bool			(*add)(struct s_m_shader *, const char *, const char *);
}					t_m_shader;
t_m_shader			*m_shader_construct();
void				*m_shader_destruct(t_m_shader **m_shader);

/*						*/
/*						*/
/*						*/

typedef struct		s_cam
{
	float			pitch;
	float			yaw;
	float			sensitivity;
	t_vector		front;
	t_vector		last_cursor_position;
	t_vector		position;
	t_vector		to;
	t_vector		up;
}					t_cam;
t_cam 		*cam_construct();
void		*cam_destruct(t_cam **cam);
void		cam_update(t_cam *cam, const t_glfw *glfw, const float delta_time);

typedef struct		s_env
{
	t_fps			*fps;
	float			delta_time;
	t_glfw			*glfw;
	t_cam			*cam;


	//to scene
	t_m_shader		*m_shader;

	int64_t			flag;
}					t_env;
t_env 				*env_construct();
void 				*env_destruct(void *ptr);



int					flag(int64_t *f, int argc, char **argv);
bool				loop(t_env *e);



t_vector			*singleton_mouse_position();
void				event_mouse(GLFWwindow *window, double pos_x, double pos_y);

float				get_degrees(const float radians);
float				get_radians(const float degrees);



t_matrix		matrixgl_view(t_cam *cam);
t_matrix		look_at_gl(const t_vector *position,
						const t_vector *to,
						const t_vector *up);
t_matrix matrixgl_get_projection(const float fov,
									const float ratio,
									const float near,
									const float far);

#endif
