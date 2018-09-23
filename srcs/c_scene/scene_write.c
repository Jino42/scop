/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:35:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/24 00:35:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "scop.h"

bool		scene_write(t_scene *scene, const char *path)
{
	cJSON	*json_scene;
	char	*str;
	int		fd;

	if ((fd = open(path, O_RDWR|O_CREAT, 0666)) <= 0)
		return (false);
	printf("%i\n", fd);
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
	str = cJSON_Print(json_scene);
	dprintf(fd, "%s\n", str);
	close(fd);
	free(str);
	cJSON_Delete(json_scene);
	return (true);
}
