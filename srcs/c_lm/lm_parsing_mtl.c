/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parsing_mtl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 22:56:41 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 23:30:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static bool	lm_parsing_mtl_basic(t_lm *lm, t_material *material)
{
	if (!strcmp(lm->type, "Ka"))
	{
		sscanf(lm->line_mtl, "%s %f %f %f\n", lm->type, &material->ambient.x,
			&material->ambient.y, &material->ambient.z);
	}
	else if (!strcmp(lm->type, "Kd"))
	{
		sscanf(lm->line_mtl, "%s %f %f %f\n", lm->type, &material->diffuse.x,
			&material->diffuse.y, &material->diffuse.z);
	}
	else if (!strcmp(lm->type, "Ks"))
	{
		sscanf(lm->line_mtl, "%s %f %f %f\n", lm->type, &material->specular.x,
			&material->specular.y, &material->specular.z);
	}
	else if (!strcmp(lm->type, "Ns"))
		sscanf(lm->line_mtl, "%s %f", lm->type, &material->shininess);
	else if (!strcmp(lm->type, "d"))
		sscanf(lm->line_mtl, "%s %f", lm->type, &material->transparency);
	return (true);
}

static bool	lm_parsing_mtl_open_file(t_lm *lm, t_model *model)
{
	char		*path_mtl;

	sscanf(lm->line, "%s %s\n", lm->type, lm->buffer255);
	if (!(path_mtl = ft_strjoin(model->access_path, lm->buffer255)))
		return (ft_bool_error("Path MTL false", NULL, NULL));
	lm->fd_mlt = open(path_mtl, O_RDONLY);
	ft_memdel((void **)&path_mtl);
	if (!lm->fd_mlt || lm->fd_mlt < 0)
		return (ft_bool_error("FD: Problème", NULL, NULL));
	bzero(lm->buffer255, 255);
	bzero(lm->name_mtl, 1024);
	return (true);
}

static bool	lm_parsing_mtl_newmtl(t_lm *lm,
								t_m_material *m_material,
								t_material **material)
{
	if (!strcmp(lm->type, "newmtl"))
	{
		if (*material)
			m_material->add(m_material, *material);
		sscanf(lm->line_mtl, "%s %s\n", lm->type, lm->name_mtl);
		if (!(*material = material_construct(lm->name_mtl, MATERIAL_MTLLIB)))
			return (false);
	}
	return (true);
}

static bool	lm_parsing_mtl_diffuse(t_lm *lm,
								t_model *model,
								t_material *material)
{
	char		*path_tex;
	t_texture	*texture;

	texture = NULL;
	if (!strcmp(lm->type, "map_Kd"))
	{
		sscanf(lm->line_mtl, "%s %s", lm->type, lm->buffer255);
		if (!(path_tex = ft_strjoin((const char *)model->access_path,
				lm->buffer255)))
			return (false);
		if (!(texture = lm->scene->m_texture->new(lm->scene->m_texture,
				MATERIAL_MAP_DIFFUSE, path_tex)))
		{
			ft_memdel((void **)&path_tex);
			return (false);
		}
		ft_memdel((void **)&path_tex);
		material_set_texture(material, texture);
	}
	return (true);
}

bool		lm_parsing_mtl(t_lm *lm, t_m_material *m_material, t_model *model)
{
	GLuint		map_id;
	t_material	*material;

	if (!(lm_parsing_mtl_open_file(lm, model)))
		return (false);
	material = NULL;
	while (get_next_line(lm->fd_mlt, &lm->line_mtl))
	{
		map_id = 0;
		sscanf(lm->line_mtl, "%s ", lm->type);
		if (!lm_parsing_mtl_newmtl(lm, m_material, &material)
			|| !lm_parsing_mtl_diffuse(lm, model, material))
			return (false);
		lm_parsing_mtl_basic(lm, material);
		bzero(lm->type, 10);
		bzero(lm->buffer255, 255);
		ft_memdel((void *)&lm->line_mtl);
	}
	if (material)
		m_material->add(m_material, material);
	return (true);
}
