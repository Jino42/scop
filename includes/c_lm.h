#ifndef C_LM_H
# define C_LM_H

# include "vector.h"
# include "c_model.h"
# include <stdint.h>

typedef struct		s_lm
{
	t_model			*model;
	t_mesh			*mesh;

	GLint			nb_v;
	GLint			nb_vt;
	GLint			nb_vn;
	GLfloat			*v;
	GLfloat			*vt;
	GLfloat			*vn;

	const char		*path;
	int				fd;

	char			type[10];
	int				buffer_index_v[4];
	int				buffer_index_vt[4];
	int				buffer_index_vn[4];
	float			buffer_v[4];
	float			buffer_vt[4];
	float			buffer_vn[4];

	uint32_t		mem_len_indices;

	uint32_t		mem_len_v;
	uint32_t		mem_len_vt;
	uint32_t		mem_len_vn;
	uint32_t		mem_len_indexed_v;
	uint32_t		mem_len_indexed_vn;
	uint32_t		mem_len_indexed_vt;

	uint32_t		last_index_v;
	uint32_t		last_index_vt;
	uint32_t		last_index_vn;
	uint32_t		last_index;
	char			*line;
}					t_lm;
bool		lm_get_vertex(t_lm *lm);
bool		lm_get_vnormal(t_lm *lm);
bool		lm_get_vtexel(t_lm *lm);
bool		lm_check_realloc(t_lm *lm);
bool		lm_add_mesh(t_lm *lm);
bool		lm_get_face(t_lm *lm);
void		*lm_destruct(t_lm **c_lm);
t_lm		*lm_construct(t_model *model, const char *path_obj);


#endif
