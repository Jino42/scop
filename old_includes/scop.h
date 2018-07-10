/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/08 21:06:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "scop_glfw.h"
# include "glad.h"
# include "libft.h"
# include "matrix.h"
# include "material.h"

# include <math.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdbool.h>
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

typedef struct		s_shader
{
	GLuint			program;

	void			(*use)(struct s_shader *);
}					t_shader;
void				*shader_destroy(t_shader **shader);
t_shader			*shader_construct(const char *vertex_shader_path,
									const char *fragment_shader_path);

typedef struct		s_texture
{
	GLuint			id;
	uint32_t		width;
	uint32_t		height;
	char			*path;
}					t_texture;
typedef struct		s_m_textures
{
	uint32_t		size;
	t_texture		**texture;
	GLuint			(*add)(struct s_m_textures *,
							const char *);
	void			(*use)(struct s_m_textures *,
							const t_shader *shader);
}					t_m_textures;
void				*textures_destroy(t_m_textures **textures);
t_m_textures			*textures_construct();

typedef struct		s_cam
{
	t_vector		position;
	t_vector		angle;
	t_vector		to;
	t_vector		up;
}					t_cam;

typedef struct		s_light
{
	t_vector		position;
	t_vector		ambient;
	t_vector		diffuse;
	t_vector		specular;
}					t_light;
t_light		*light_construct();
void		*light_destruct(t_light **light);

typedef struct		s_material
{
	char			*name;
	t_vector		ambient;
	t_vector		diffuse;
	t_vector		specular;
	GLfloat			shininess;
	GLfloat			transparency;
	GLuint			texture_ambient;
	GLuint			texture_diffuse;
	GLuint			texture_specular;
	GLuint			texture_shininess;
	GLuint			texture_normal;
	uint32_t		flag;
	bool			(*set_map)(struct s_material *,
								uint32_t,
								const GLuint);
}					t_material;
typedef struct		s_m_materials
{
	uint32_t		size;
	t_material		**material;
	char			**path;
	bool			(*add)(struct s_m_materials *, struct s_material *);
	t_material		*(*search)(struct s_m_materials *, const char *);
}					t_m_materials;
t_m_materials			*materials_construct();
void				*material_destruct(t_material **material);
t_material			*material_construct();
t_material			*material_construct_tab();

typedef struct		s_mesh
{
	GLuint			VBO;
	GLuint			VNBO;
	GLuint			VTBO;
	GLuint			EBO;
	GLuint			VAO;

	t_material		*material;

	GLfloat			*v;
	GLfloat			*vt;
	GLfloat			*vn;
	GLfloat			*indexed_v;
	GLfloat			*indexed_vt;
	GLfloat			*indexed_vn;
	GLuint			*indices;
	GLint			nb_v;
	GLint			nb_vt;
	GLint			nb_vn;
	GLint			nb_indexed_v;
	GLint			nb_indexed_vt;
	GLint			nb_indexed_vn;
	GLint			nb_faces;
	GLint			nb_indices;
}					t_mesh;
void				*mesh_destroy(t_mesh **mesh);
t_mesh				*mesh_construct(const char *path_obj,
						const char *shader_vert_path,
						const char *shader_frag_path,
						const char *texture_path);
typedef struct		s_m_meshs
{
	uint32_t		size;
	t_mesh			**mesh;
	//				ADD;
}					t_m_meshs;
t_m_meshs				*construct_m_meshs();

typedef struct		s_model
{
	unsigned char 	*path;
	t_m_textures	*textures;
	t_m_materials	*materials;
	t_m_meshs		*meshs;
	t_matrix		transform;
	GLenum			type_draw;

	uint32_t		flag;
	void			(*render)(struct s_model *,
						t_cam *, t_light *,
						t_matrix *, t_matrix *);
}					t_model;
void				*model_destroy(t_model **model);
t_model				*model_construct(const char *path,
									const char *path_obj,
									const char *path_textures);
void		model_render(t_model *model, t_cam *cam, t_light *light,
								t_matrix *view, t_matrix *projection,
								t_shader *shader);

typedef struct		s_camfps
{
	float			pitch;
	float			yaw;
	t_vector		front;
}					t_event_camfps;

typedef struct		s_glfw
{
	GLFWwindow		*window;
}					t_glfw;

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
	int8_t			index_material;
	t_material		*material;
}					t_env;

bool				obj_pars(t_model *model, const char * path_obj);
bool				parsing_mtl(t_model *model, const char *path_mtl);

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

t_matrix		look_at(const t_vector *position,
						const t_vector *to,
						const t_vector *up);
t_matrix		matrix_get_projection_opengl(const float fov,
												const float ratio,
												const float near,
												const float far);

#endif