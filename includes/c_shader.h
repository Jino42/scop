#ifndef C_SHADER_H
# define C_SHADER_H

# include "vector.h"
# include "cJSON.h"
# include <stdint.h>
# include "glad.h"

# define SHADER_INDEX_LIGHT				0
# define SHADER_INDEX_OUTLINE			1
# define SHADER_INDEX_DYNAMIQUE_TEXTURE	2

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
GLboolean			shader_build_shader_program(t_shader *shader,
									const GLint vertex_shader,
									const GLint fragment_shader);
GLboolean			shader_build_shader(GLint *shader, const GLenum shader_type,
									const char *shader_path);
void				shader_use(t_shader *shader);
typedef struct		s_m_shader
{
	unsigned int	size;
	t_shader		**shader;
	char			**shader_name;
	int				index_selected;
	bool			(*add)(struct s_m_shader *, const char *, const char *, const char *);
}					t_m_shader;
t_m_shader			*m_shader_construct_hidden(void);
t_m_shader			*m_shader_construct();
void				*m_shader_destruct(t_m_shader **m_shader);
bool				m_shader_json_parse(t_m_shader *m_shader, cJSON *get, const char *key);
bool				m_shader_json_write(t_m_shader *m_shader, cJSON *json_scene);
int					m_shader_get_index(t_m_shader *m_shader, char *str);


#endif
