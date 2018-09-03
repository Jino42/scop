#ifndef C_TEXTURE_H
# define C_TEXTURE_H

# include "vector.h"
# include <stdint.h>

typedef struct		s_texture
{
	char			*name;
	GLuint			id;
	unsigned int	width;
	unsigned int	height;
	int				flag;
}					t_texture;
void				*texture_destruct(t_texture **texture);
t_texture			*texture_construct(const char *name, const int type);

typedef struct		s_m_texture
{
	int				index_selected;
	unsigned int	size;
	t_texture		**texture;
	char			**texture_name;
	bool			(*add)(struct s_m_texture *, t_texture *);
	t_texture		*(*new)(struct s_m_texture *, const int type, const char *);
}					t_m_texture;
t_m_texture			*m_texture_construct();
void				*m_texture_destruct(t_m_texture **m_model);
bool				m_texture_json_parse(t_m_texture *m_texture, cJSON *get, const char *key);

#endif
