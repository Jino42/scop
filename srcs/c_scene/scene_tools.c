/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:36:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/24 00:36:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		scene_shader_add(t_scene *scene,
						const char *vertex_shader_path,
						const char *fragment_shader_path,
						const char *name)
{
	scene->m_shader->add(scene->m_shader, vertex_shader_path, fragment_shader_path, name);
	return (true);
}

bool		scene_mesh_add(t_scene *scene, t_mesh *mesh)
{
	scene->m_mesh->add(scene->m_mesh, mesh);
	return (true);
}

bool		scene_model_add(t_scene *scene, t_model *model)
{
	scene->m_model->add(scene->m_model, model);
	return (true);
}

bool		scene_reload(t_scene **scene, const char *path)
{
	int flag;

	flag = (*scene)->flag;
	scene_destruct(scene);
	if (!((*scene) = scene_construct(path, flag)))
		return (false);
	if (!scene || !(*scene))
		return (false);
	return (true);
}
