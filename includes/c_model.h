/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_model.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:06:41 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 23:18:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_MODEL_H
# define C_MODEL_H

# include <stdint.h>
# include "scop_glfw.h"

# define MODEL_USE_BASIC					(1 << 10)
# define MODEL_USE_TEXTURE					(1 << 11)
# define MODEL_USE_MATERIAL_PERSONNAL		(1 << 12)
# define MODEL_SAME_SCALING					(1 << 13)
# define MODEL_USE_DYNAMIQUE_TEXTURE		(1 << 14)
# define MODEL_ROTATE						(1 << 15)

# define MODEL_INDEX_LIGHT_BASIC			1
# define MODEL_INDEX_LIGHT_DIRECTIONNAL		0
# define MODEL_INDEX_LIGHT_POINT			1
# define MODEL_INDEX_LIGHT_SPOT				0
# define MODEL_INDEX_PLAN					2
# define MODEL_USE_FLAG_TMP1 (MODEL_USE_TEXTURE | MODEL_USE_MATERIAL_PERSONNAL)
# define MODEL_USE_FLAG_TMP2 (MODEL_USE_DYNAMIQUE_TEXTURE | MODEL_USE_BASIC)
# define MODEL_USE_FLAG	(MODEL_USE_FLAG_TMP1 | MODEL_USE_FLAG_TMP2)

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
	int				last_flag;
	int				temp_flag;
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
	int				timestamp;
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
bool				m_model_add(t_m_model *m_model, t_model *model);
t_model				*m_model_new(t_m_model *m_model, char *path, char *name);
bool				m_model_json_write(t_m_model *m_model, cJSON *json_scene);
void				m_model_setup(t_m_model *m_model);
void				m_model_update(t_m_model *m_model);

#endif
