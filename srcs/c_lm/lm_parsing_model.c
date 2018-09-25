/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_model.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 23:09:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 23:13:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static bool		lm_parsing_basic_mtl(t_lm *lm)
{
	if (!strcmp("usemtl", lm->type))
	{
		if (lm->mesh->index_material_personnal)
		{
			lm->nb_mesh++;
			if (!(lm_add_mesh(lm, lm->mesh->flag)))
				return (false);
		}
		sscanf(lm->line, "%s %s\n", lm->type, lm->buffer255);
		lm->mesh->index_material_personnal =
			m_material_get_index(lm->scene->m_material_personnal,
			lm->buffer255);
	}
	else if (!strcmp("o", lm->type) && lm->mesh->nb_indices)
	{
		lm->nb_mesh++;
		if (!(lm_add_mesh(lm, 0)))
			return (false);
	}
	return (true);
}

static bool		lm_parsing_basic(t_scene *scene, t_lm *lm, t_model *model)
{
	if (!strcmp("vn", lm->type))
		lm_get_vnormal(lm);
	else if (!strcmp("vt", lm->type))
		lm_get_vtexel(lm);
	else if (!strcmp("v", lm->type))
		lm_get_vertex(lm);
	else if (!strcmp("f", lm->type))
	{
		if (!lm_get_face(lm))
			return (false);
	}
	else if (!strcmp("mtllib", lm->type))
	{
		if (!(lm_parsing_mtl(lm, scene->m_material_personnal, model)))
			return (false);
	}
	return (lm_parsing_basic_mtl(lm));
}

static void		lm_parsing_basic_bzero(t_lm *lm)
{
	ft_strdel(&lm->line);
	bzero(lm->type, 10);
	bzero(lm->buffer255, 255);
	bzero(lm->buffer_index_v, 4 * sizeof(int));
	bzero(lm->buffer_index_vt, 4 * sizeof(int));
	bzero(lm->buffer_index_vn, 4 * sizeof(int));
	bzero(lm->buffer_v, 4 * sizeof(int));
	bzero(lm->buffer_vt, 4 * sizeof(int));
	bzero(lm->buffer_vn, 4 * sizeof(int));
}

t_model			*m_model_load(t_scene *scene,
							t_m_model *m_model,
							const char *path_obj,
							const char *name)
{
	t_model	*model;
	t_lm	*lm;

	model = model_construct(path_obj, name);
	if (!(lm = lm_construct(scene, model, path_obj)))
	{
		model_destruct(&model);
		return (false);
	}
	while (get_next_line(lm->fd, &lm->line) == 1)
	{
		sscanf(lm->line, "%s ", lm->type);
		if (!lm_parsing_basic(scene, lm, model))
			return (lm_destruct(&lm, &lm->model));
		if (!(lm_check_realloc(lm)))
			return (lm_destruct(&lm, &lm->model));
		lm_parsing_basic_bzero(lm);
	}
	glfwPollEvents();
	model_gen_gl_buffers(model);
	model_setup_scaling(model);
	if (!(m_model->add(m_model, model)))
		return (lm_destruct(&lm, &lm->model));
	lm_destruct(&lm, NULL);
	return (model);
}
