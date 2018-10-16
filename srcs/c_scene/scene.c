/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 20:02:02 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 16:53:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_scene	*scene_construct_2(t_scene *scene, const char *path)
{
	if (!(scene->m_material_personnal = m_material_construct()))
		return (scene_destruct(&scene));
	if (!(m_material_add_default(scene->m_material_personnal)))
		return (scene_destruct(&scene));
	if (!(scene->m_light = m_light_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_texture = m_texture_construct()))
		return (scene_destruct(&scene));
	if (!(scene->cam = cam_construct()))
		return (scene_destruct(&scene));
	if (!(scene_parse(scene, path)))
		return (scene_destruct(&scene));
	if (!scene_require(scene))
		return (scene_destruct(&scene));
	if (!m_model_hidden_setup(scene))
		return (scene_destruct(&scene));
	return (scene);
}

t_scene			*scene_construct(const char *path, const int flag)
{
	t_scene *scene;

	(void)path;
	if (!(scene = ft_memalloc(sizeof(t_scene))))
		return (NULL);
	if (flag)
		scene->flag |= SCOP_INDEXING;
	scene->path = path;
	scene->shader_add = &scene_shader_add;
	scene->model_add = &scene_model_add;
	scene->mesh_add = &scene_mesh_add;
	if (!(scene->m_model_hidden = m_model_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_model = m_model_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_mesh = m_mesh_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_shader_hidden = m_shader_construct_hidden()))
		return (scene_destruct(&scene));
	if (!(scene->m_shader = m_shader_construct()))
		return (scene_destruct(&scene));
	if (!(scene->m_material = m_material_construct()))
		return (scene_destruct(&scene));
	return (scene_construct_2(scene, path));
}

static void		scene_destruct_2(t_scene **scene)
{
	if ((*scene)->m_material)
		m_material_destruct(&(*scene)->m_material);
	if ((*scene)->m_material_personnal)
		m_material_destruct(&(*scene)->m_material_personnal);
	if ((*scene)->m_light)
		m_light_destruct(&(*scene)->m_light);
	if ((*scene)->cam)
		cam_destruct(&(*scene)->cam);
	if ((*scene)->m_texture)
		m_texture_destruct(&(*scene)->m_texture);
}

void			*scene_destruct(t_scene **scene)
{
	if (scene && *scene)
	{
		if ((*scene)->m_model_hidden)
			m_model_destruct(&(*scene)->m_model_hidden);
		if ((*scene)->m_model)
			m_model_destruct(&(*scene)->m_model);
		if ((*scene)->m_mesh)
			m_mesh_destruct(&(*scene)->m_mesh);
		if ((*scene)->m_shader_hidden)
			m_shader_destruct(&(*scene)->m_shader_hidden);
		if ((*scene)->m_shader)
			m_shader_destruct(&(*scene)->m_shader);
		scene_destruct_2(scene);
		ft_memdel((void **)scene);
	}
	return (NULL);
}
