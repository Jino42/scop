#ifndef C_MODEL_H
# define C_MODEL_H

# include <stdint.h>
# include "scop_glfw.h"

# define MODEL_USE_MATERIAL_PERSONNAL		(1 << 0)


typedef struct		s_model
{
	bool			update;
	char			*name;
	char			*path;
	char			*access_path;
	t_m_mesh		*m_mesh;
	t_matrix		transform;
	GLenum			type_draw;
	int				flag;
	float			same_scaling;
	float			inter_scaling;
	t_vector		min;
	t_vector		max;
	t_vector		center;
	t_vector		negative_center;

	t_vector		position;
	t_vector		rotation;
	t_vector		scaling;

	unsigned int	index_shader;
	unsigned int	index_material;
	unsigned int	index_material_personnal;
}					t_model;
void				model_setup_scaling(t_model *model);
void				*model_destruct(t_model **model);
t_model				*model_construct(const char *path, const char *name);
void				model_compute_transform(t_model *model);
void				model_update(t_model *model);
void				model_gen_gl_buffers(t_model *model);

typedef struct		s_m_model
{
	int				index_selected;
	unsigned int	size;
	t_model			**model;
	char			**model_name;
	bool			(*add)(struct s_m_model *, t_model *);
	t_model			*(*new)(struct s_m_model *, char *, char *);
}					t_m_model;
t_m_model			*m_model_construct();
void				*m_model_destruct(t_m_model **m_model);
t_model				*m_model_new(t_m_model *m_model, char *path, char *name);
bool				m_model_json_write(t_m_model *m_model, cJSON *json_scene);

#endif
