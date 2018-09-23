/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/24 00:17:14 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "scop_glfw.h"
# include "libft.h"
# include "matrix.h"
# include "json.h"

# include <math.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

# include "c_scene.h"
# include "c_lm.h"
# include "c_rbo.h"

# define DEBUG 1

# define BUFFER_OBJ (2048)

# define WIDTH 1920
# define HEIGHT 1080

# define SCOP_V (1 << 1)
# define SCOP_VT (1 << 2)
# define SCOP_VN (1 << 3)
# define F_TEXTURE (1 << 4)
# define SCOP_MAX_LIGHTS 8

# define FLOAT_MIN -100000.f
# define FLOAT_MAX 100000.f

# define MAX_SOURCE_SIZE 8000
# define BUFFER_LOG 2048

# define CURSOR_NORMAL (1 << 0)
# define CURSOR_HIDDEN (1 << 0)

typedef struct		s_vector3f
{
	float			x;
	float			y;
	float			z;
}					t_vector3f;

typedef struct		s_vector2f
{
	float			x;
	float			y;
}					t_vector2f;

typedef struct		s_fps
{
	struct timeval	step2;
	struct timeval	step;
	struct timeval	cur;
	float			time;
	float			delta_time;
	unsigned int	fps;
	unsigned int	ret_fps;
}					t_fps;
t_fps				*fps_construct();
void				*fps_destruct(t_fps **e);
void				fps_update(t_fps *fps, float *ptr);
 int		fps_timestamp(t_fps *fps);

typedef struct		s_env
{
	t_fps			*fps;
	float			delta_time;
	t_glfw			*glfw;

	t_scene			*scene;

	int64_t			flag;
}					t_env;

t_env				*env_construct(int argc, char **argv);
void				*env_destruct(void *ptr);
int					flag(int64_t *f, int argc, char **argv);
bool				loop(t_env *e);
t_vector			*singleton_mouse_position();
void				event_mouse(GLFWwindow *window, double pos_x, double pos_y);
float				get_degrees(const float radians);
float				get_radians(const float degrees);
t_matrix			matrixgl_view(t_cam *cam);
t_matrix			look_at_gl(const t_vector *position,
						const t_vector *to, const t_vector *up);
t_matrix			matrixgl_get_projection(const float fov,
						const float ratio, const float near, const float far);
t_model				*m_model_load(t_scene *scene, t_m_model *m_model,
						const char *path_obj, const char *name);
void				scene_render(t_scene *scene, float time, unsigned int timestamp);
bool				m_model_hidden_setup(t_scene *scene);
void				rbo_render(t_rbo *rbo, t_shader *shader, t_model *model,
						const float time);
void				cam_update(t_cam *cam, const t_glfw *glfw,
						const float delta_time);
bool				nk_scene(t_nk *nk, t_scene **scene);
bool				nk_scene_menu(t_nk *nk, t_scene **scene);
void				nk_cam(t_nk *nk, t_cam *cam);
void				nk_m_model(t_nk *nk, t_scene *scene, t_m_model *m_model);
void				nk_model(t_nk *nk, t_scene *scene, t_model *model);
void				nk_material(t_nk *nk, t_material *material);
void				nk_m_material(t_nk *nk, t_m_material *m_material);
void				nk_m_light(t_nk *nk, t_scene *scene, t_m_light *m_light);
void				nk_light(t_nk *nk, t_light *light);

#endif
