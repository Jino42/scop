#ifndef C_LIGHT_H
# define C_LIGHT_H

# include "vector.h"
# include <stdint.h>

# define LIGHT_BASIC (1 << 0)
# define LIGHT_DIRECTIONNAL (1 << 1)
# define LIGHT_POINT (1 << 2)

typedef struct		s_light
{
	char			*name;
	t_vector		ambient;
	t_vector		diffuse;
	t_vector		specular;
	t_vector		position;
	t_vector		direction;
	int				flag;
}					t_light;
void				*light_destruct(t_light **light);
t_light				*light_construct(char *name);

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
bool				m_light_json_parse(t_m_light *m_light, cJSON *get, const char *key);
bool				m_light_json_write(t_m_light *m_light, cJSON *json_scene);

#endif
