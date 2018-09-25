/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:07:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 19:55:50 by ntoniolo         ###   ########.fr       */
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
	const char		*path;
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
bool				scene_parse(t_scene *scene, const char *path);
bool				scene_require(t_scene *scene);
bool				scene_write(t_scene *scene, const char *path);
bool				scene_reload(t_scene **scene, const char *path);

bool				m_model_json_parse_material(cJSON *get, const char *key,
						t_scene *scene, t_model *model);
bool				m_model_json_parse_shader(cJSON *get, const char *key,
						t_scene *scene, t_model *model);

bool				scene_model_add(t_scene *scene, t_model *model);
bool				scene_mesh_add(t_scene *scene, t_mesh *mesh);
bool				m_light_render(t_scene *scene);
bool				scene_shader_add(t_scene *scene,
						const char *vertex_shader_path,
						const char *fragment_shader_path,
						const char *name);
void		scene_set_uniform_lights(t_m_light *m_light, t_shader *shader);

void		scene_set_uniform_texture_basic(t_shader *shader, t_model *model, t_material *material);
void		scene_set_uniform_texture_personnal(t_shader *shader, t_material *material_personnal);
void		scene_set_uniform_texture_dynamique(t_scene *scene, t_shader *shader);
void		scene_set_uniform_material(t_shader *shader, t_material *material);
void		scene_set_uniform_material_personnal(t_shader *shader, t_material *material_personnal);
void		scene_set_uniform_data(t_scene *scene, t_shader *shader, t_model *model);
void		scene_set_uniform_time(t_scene *scene, t_shader *shader, t_model *model, float time);
#endif
