/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/18 23:41:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "scop_glfw.h"
# include "glad.h"
# include "libft.h"
# include "matrix.h"

# include <math.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>

# define WIDTH 1920
# define HEIGHT 1080

#define MAX_SOURCE_SIZE 2000
#define BUFFER_LOG 2048

typedef struct		s_shader
{
	GLuint			program;

	void			(*use)(struct s_shader *);
}					t_shader;

typedef struct	s_asset
{
	t_shader	*shader;
	//tex
	GLuint		VBO;
	GLuint		VAO;
	GLuint		EBO;
	GLfloat		*vertices;
	GLuint		*indices;

	GLenum		type_draw;
	GLint		nb_vertices;
	GLint		nb_faces;
	GLint		nb_indices;
}				t_asset;

typedef struct	s_model
{
	t_asset		*asset;
	t_matrix	transform;
}				t_model;

typedef struct	s_camfps
{
	float		pitch;
	float		yaw;
	t_vector	front;
}				t_event_camfps;

typedef struct		s_cam
{
	t_vector		position;
	t_vector		angle;
	t_vector		to;
	t_vector		up;
}					t_cam;

typedef struct	s_glfw
{
	GLFWwindow	*window;
}				t_glfw;

typedef struct		s_fps
{
	struct timeval	step2;
	struct timeval	step;
	struct timeval	cur;
	float			delta_time;
	unsigned int	fps;
	unsigned int	ret_fps;
}					t_fps;

typedef struct		s_env
{
	t_fps			fps;
	t_glfw			glfw;

	t_cam			cam;

	int64_t			flag;
}					t_env;

bool				obj_pars(t_asset *asset, const char * path_obj);

int					flag(int64_t *f, int argc, char **argv);
bool				render_loop(t_env *e, const char **argv, t_glfw *glfw);
int					end_of_program(t_env *e, char *str, int flag);

bool				glfw_init(t_glfw *glfw);
void				glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void				glfw_input(t_glfw *glfw);

void				update_fps(t_fps *fps);

t_matrix			matrix_view(t_cam *cam);


t_event_camfps		*singleton_mouse();
void				event_mouse(GLFWwindow *window, double pos_x, double pos_y);
void				event_cam(t_env *e, t_cam *cam, t_glfw *glfw);

float				get_degrees(const float radians);
float				get_radians(const float degrees);

GLboolean			shader_construct(t_shader *shader,
									const char *vertex_shader_path,
									const char *fragment_shader_path);



t_matrix		look_at(const t_vector *position,
						const t_vector *to,
						const t_vector *up);
t_matrix		matrix_get_projection_opengl(const float fov,
												const float ratio,
												const float near,
												const float far);

#endif
