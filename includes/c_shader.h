#ifndef C_SHADER_H
# define C_SHADER_H

# include "vector.h"
# include "cJSON.h"
# include <stdint.h>
# include "glad.h"

typedef struct		s_shader
{
	GLuint			program;
	char			*name;
	char			*path_vertex;
	char			*path_fragment;
	void			(*use)(struct s_shader *);
}					t_shader;
void				*shader_destruct(t_shader **shader);
t_shader			*shader_construct(const char *vertex_shader_path,
									const char *fragment_shader_path,
									const char *name);

typedef struct		s_m_shader
{
	unsigned int	size;
	t_shader		**shader;
	char			**shader_name;
	int				index_selected;
	bool			(*add)(struct s_m_shader *, const char *, const char *, const char *);
}					t_m_shader;
t_m_shader			*m_shader_construct();
void				*m_shader_destruct(t_m_shader **m_shader);
int					m_shader_get_index(t_m_shader *m_shader, char *str);
bool				m_shader_json_parse(t_m_shader *m_shader, cJSON *get, const char *key);


#endif
