/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_lm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:42:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 23:16:18 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_LM_H
# define C_LM_H

# include "vector.h"
# include "c_model.h"
# include <stdint.h>

typedef struct		s_lm
{
	t_scene			*scene;
	t_model			*model;
	t_mesh			*mesh;

	GLint			nb_v;
	GLint			nb_vt;
	GLint			nb_vn;
	GLfloat			*v;
	GLfloat			*vt;
	GLfloat			*vn;

	const char		*path;

	char			type[10];
	char			buffer255[255];
	int				buffer_index_v[4];
	int				buffer_index_vt[4];
	int				buffer_index_vn[4];
	float			buffer_v[4];
	float			buffer_vt[4];
	float			buffer_vn[4];

	uint32_t		nb_mesh;
	uint32_t		mem_len_indices;

	uint32_t		mem_len_v;
	uint32_t		mem_len_vt;
	uint32_t		mem_len_vn;
	uint32_t		mem_len_u;
	uint32_t		mem_len_indexed_v;
	uint32_t		mem_len_indexed_vn;
	uint32_t		mem_len_indexed_vt;
	uint32_t		mem_len_indexed_color;
	uint32_t		mem_len_indexed_u;

	uint32_t		last_index_v;
	uint32_t		last_index_vt;
	uint32_t		last_index_vn;
	uint32_t		last_index;
	char			*line;
	int				fd;
	int				fd_mlt;
	char			*line_mtl;
	char			name_mtl[1024];
}					t_lm;
bool				lm_get_vertex(t_lm *lm);
bool				lm_get_vnormal(t_lm *lm);
bool				lm_get_vtexel(t_lm *lm);
bool				lm_check_realloc(t_lm *lm);
bool				lm_add_mesh(t_lm *lm, int flag);
bool				lm_get_face(t_lm *lm);
void				*lm_destruct(t_lm **c_lm, t_model **model);
t_lm				*lm_construct(t_scene *scene,
									t_model *model, const char *path_obj);
bool				lm_indexing_face(t_lm *lm, t_mesh *mesh, const int sommet4);
void				lm_indexing_calculate_vt(t_mesh *mesh);
void				lm_indexing_calculate_normal(t_mesh *mesh);
bool				lm_parsing_mtl(t_lm *lm, t_m_material *m_material,
						t_model *model);
#endif
