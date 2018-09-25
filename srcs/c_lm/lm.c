/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 00:04:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/26 00:09:37 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	lm_construct_set_mem_len(t_lm *lm)
{
	lm->mem_len_indices = BUFFER_OBJ * sizeof(GLuint);
	lm->mem_len_indexed_v = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_vn = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_vt = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_color = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_u = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_v = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_vt = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_vn = BUFFER_OBJ * sizeof(GLfloat);
}

t_lm		*lm_construct(t_scene *scene, t_model *model, const char *path_obj)
{
	t_lm	*lm;
	int		fd;

	fd = open(path_obj, O_RDONLY);
	if (!fd || fd < 0)
		return (NULL);
	if (!(lm = ft_memalloc(sizeof(t_lm))))
		return (NULL);
	lm->model = model;
	lm->scene = scene;
	if (!(lm->mesh = lm->model->m_mesh->new(lm->model->m_mesh)))
		return (lm_destruct(&lm, &lm->model));
	if (!(lm->v = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm, &lm->model));
	if (!(lm->vt = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm, &lm->model));
	if (!(lm->vn = ft_memalloc(sizeof(GLfloat) * BUFFER_OBJ)))
		return (lm_destruct(&lm, &lm->model));
	lm_construct_set_mem_len(lm);
	lm->fd = fd;
	return (lm);
}

void		*lm_destruct(t_lm **c_lm, t_model **model)
{
	t_lm	*lm;

	if (c_lm && *c_lm)
	{
		lm = *c_lm;
		ft_memdel((void **)&lm->v);
		ft_memdel((void **)&lm->vt);
		ft_memdel((void **)&lm->vn);
		ft_memdel((void **)c_lm);
	}
	if (model && *model)
		model_destruct(model);
	return (NULL);
}

bool		lm_add_mesh(t_lm *lm, int flag)
{
	if (!(lm->mesh = lm->model->m_mesh->new(lm->model->m_mesh)))
		return (lm_destruct(&lm, &lm->model));
	lm->mem_len_indices = BUFFER_OBJ * sizeof(GLuint);
	lm->mem_len_indexed_v = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_vn = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_vt = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_indexed_color = BUFFER_OBJ * sizeof(GLfloat);
	lm->mem_len_u = BUFFER_OBJ * sizeof(GLfloat);
	lm->mesh->flag = flag;
	return (true);
}
