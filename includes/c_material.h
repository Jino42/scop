/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_material.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:43:24 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 00:43:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_MATERIAL_H
# define C_MATERIAL_H

# include "vector.h"
# include <stdint.h>

# define MATERIAL_MTLLIB			(1 << 0)
# define MATERIAL_MAP_SHININESS		(1 << 1)
# define MATERIAL_MAP_NORMAL		(1 << 2)
# define MATERIAL_MAP_SPECULAR		(1 << 3)
# define MATERIAL_MAP_DIFFUSE		(1 << 4)
# define MATERIAL_MAP_AMBIENT		(1 << 5)

typedef struct		s_material
{
	t_vector		diffuse;
	t_vector		ambient;
	t_vector		specular;
	float			shininess;
	float			transparency;
	char			*name;
	int				flag;
	GLuint			texture_shininess;
	GLuint			texture_normal;
	GLuint			texture_specular;
	GLuint			texture_diffuse;
	GLuint			texture_ambient;
}					t_material;
void				*material_destruct(t_material **material);
t_material			*material_construct(char *name, const int material_type);
bool				material_set_map(t_material *material, uint32_t flag,
													const GLuint map_id);
bool				material_set_texture(t_material *material,
													const t_texture *texture);

typedef struct		s_m_material
{
	int				index_selected;
	unsigned int	size;
	t_material		**material;
	char			**material_name;
	bool			(*add)(struct s_m_material *, t_material *);
	t_material		*(*new)(struct s_m_material *, char *, const int);
}					t_m_material;
t_m_material		*m_material_construct();
void				*m_material_destruct(t_m_material **m_material);
bool				m_material_add_default(t_m_material *m_material);
bool				m_material_json_parse(t_m_material *m_material, cJSON *get,
												const char *key);
bool				m_material_json_write(t_m_material *m_material,
												cJSON *json_scene);
int					m_material_get_index(t_m_material *m_material, char *str);

#endif
