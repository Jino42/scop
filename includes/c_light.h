/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_light.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:42:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 17:02:14 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_LIGHT_H
# define C_LIGHT_H

# include "vector.h"
# include "c_model.h"
# include <stdint.h>

# define LIGHT_BASIC				(1 << 0)
# define LIGHT_DIRECTIONNAL			(1 << 1)
# define LIGHT_POINT				(1 << 2)

typedef struct		s_light
{
	char			*name;
	bool			update;
	t_vector		ambient;
	t_vector		diffuse;
	t_vector		specular;
	t_vector		position;
	t_vector		direction;
	t_vector		rotation;
	t_matrix		transform;
	float			constent;
	float			linear;
	float			quadratic;
	float			spot_little_radius;
	float			spot_big_radius;
	int				flag;
	float			intensity;
}					t_light;
void				*light_destruct(t_light **light);
t_light				*light_construct(char *name);
void				light_compute_transform(t_light *light, t_model *model);

typedef struct		s_m_light
{
	int				index_selected;
	unsigned int	size;
	t_light			**light;
	char			**light_name;
	bool			(*add)(struct s_m_light *, t_light *);
	t_light			*(*new)(struct s_m_light *, char *);
}					t_m_light;
t_m_light			*m_light_construct();
void				*m_light_destruct(t_m_light **m_model);
bool				m_light_json_parse(t_m_light *m_light,
											cJSON *get, const char *key);
bool				m_light_json_write(t_m_light *m_light, cJSON *json_scene);

#endif
