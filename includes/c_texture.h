#ifndef C_TEXTURE_H
# define C_TEXTURE_H

# include "vector.h"
# include <stdint.h>

typedef struct		s_texture
{
	char			*name;
	t_vector		ambient;
	t_vector		diffuse;
	t_vector		specular;
	t_vector		position;
	int				flag;
}					t_texture;
void				*texture_destruct(t_texture **texture);
t_texture			*texture_construct(char *name);

typedef struct		s_m_texture
{
	int				index_selected;
	unsigned int	size;
	t_texture		**texture;
	char			**texture_name;
	bool			(*add)(struct s_m_texture *, t_texture *);
	t_texture		*(*new)(struct s_m_texture *, char *);
}					t_m_texture;
t_m_texture			*m_texture_construct();
void				*m_texture_destruct(t_m_texture **m_model);


#endif
