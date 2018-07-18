#ifndef C_MATERIAL_H
# define C_MATERIAL_H

# include "vector.h"
# include <stdint.h>

# define MATERIAL_MTLLIB (1 << 0)

typedef struct		s_material
{
	t_vector		diffuse;
	t_vector		ambient;
	t_vector		specular;
	float			shininess;
	char			*name;
	int				flag;
}					t_material;
void				*material_destruct(t_material **material);
t_material			*material_construct(char *name, const int material_type);

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
bool				m_material_json_parse(t_m_material *m_material, cJSON *get, const char *key);
bool				m_material_json_write(t_m_material *m_material, cJSON *json_scene);
int					m_material_get_index(t_m_material *m_material, char *str);

#endif
