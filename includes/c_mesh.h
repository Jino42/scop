/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_mesh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:43:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 00:46:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_MESH_H
# define C_MESH_H

# include "vector.h"
# include <stdint.h>
# include "glad.h"

typedef struct		s_mesh
{
	GLuint			vbo;
	GLuint			vnbo;
	GLuint			vtbo;
	GLuint			colorbo;
	GLuint			ebo;
	GLuint			vao;

	GLfloat			*indexed_v;
	GLfloat			*indexed_vt;
	GLfloat			*indexed_vn;
	GLfloat			*indexed_color;
	GLuint			*indices;

	GLint			nb_faces;
	GLint			nb_indices;
	int				flag;
	unsigned int	index_material;
	unsigned int	index_material_personnal;
}					t_mesh;
void				*mesh_destruct(t_mesh **mesh);
t_mesh				*mesh_construct();
void				mesh_gen_gl_buffers(t_mesh *mesh);

typedef struct		s_m_mesh
{
	unsigned int	size;
	t_mesh			**mesh;
	bool			(*add)(struct s_m_mesh *, t_mesh *);
	t_mesh			*(*new)(struct s_m_mesh *);
}					t_m_mesh;
t_m_mesh			*m_mesh_construct();
void				*m_mesh_destruct(t_m_mesh **m_mesh);

#endif
