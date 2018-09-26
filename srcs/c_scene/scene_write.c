/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:35:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/26 17:42:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "scop.h"

static bool	scene_write_open_fd(int *fd, const char *path)
{
	if ((*fd = open(path, O_RDWR | O_CREAT | S_IRWXU)) <= 0)
	{
		if ((*fd = open(path, O_RDWR)) <= 0)
		{
			dprintf(2, "Fd error\n");
			return (false);
		}
	}
	return (true);
}

static void	scene_write_json(int fd, cJSON *json_scene)
{
	char	*str;

	str = cJSON_Print(json_scene);
	dprintf(fd, "%s\n", str);
	free(str);
}

bool		scene_write(t_scene *scene, const char *path)
{
	cJSON	*json_scene;
	int		fd;

	if (!scene_write_open_fd(&fd, path))
		return (false);
	if (!(json_scene = cJSON_CreateObject()))
	{
		close(fd);
		return (false);
	}
	if (!m_model_json_write(scene->m_model, json_scene) ||
		!m_shader_json_write(scene->m_shader, json_scene) ||
		!m_light_json_write(scene->m_light, json_scene) ||
		!m_material_json_write(scene->m_material, json_scene))
	{
		close(fd);
		cJSON_Delete(json_scene);
		return (false);
	}
	scene_write_json(fd, json_scene);
	close(fd);
	cJSON_Delete(json_scene);
	return (true);
}
