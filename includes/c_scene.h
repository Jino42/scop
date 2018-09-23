/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:07:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/23 18:11:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_SCENE_H
# define C_SCENE_H

# include "c_cam.h"
# include "c_shader.h"
# include "c_mesh.h"
# include "c_model.h"
# include "c_texture.h"
# include "c_material.h"
# include "c_light.h"
# include "c_rbo.h"

# define SCOP_INDEXING (1 << 0)

typedef struct		s_scene
{
	unsigned int	timestamp;
	int				flag;
	t_rbo			*rbo;
	int				index_light;
	t_cam			*cam;

	t_m_shader		*m_shader;
	t_m_shader		*m_shader_hidden;
	t_m_mesh		*m_mesh;
	t_m_model		*m_model_hidden;
	t_m_model		*m_model;
	t_m_material	*m_material;
	t_m_material	*m_material_personnal;
	t_m_light		*m_light;
	t_m_texture		*m_texture;
	bool			(*shader_add)(struct s_scene*, const char *,
						const char *, const char *);
	bool			(*mesh_add)(struct s_scene*, t_mesh *);
	bool			(*model_add)(struct s_scene*, t_model *);
}					t_scene;
void				*scene_destruct(t_scene **scene);
t_scene				*scene_construct(const char *path, const int flag);
bool				m_model_json_parse(t_scene *scene, cJSON *get,
						const char *key);
bool				scene_require(t_scene *scene);
bool				scene_write(t_scene *scene, const char *path);
bool				scene_reload(t_scene **scene, const char *path);

bool				m_model_json_parse_material(cJSON *get, const char *key,
						t_scene *scene, t_model *model);
bool				m_model_json_parse_shader(cJSON *get, const char *key,
						t_scene *scene, t_model *model);

bool				m_light_render(t_scene *scene);

#endif
