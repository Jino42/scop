/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_require.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:28:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/27 20:40:37 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		scene_require_index_m_model(t_scene *scene)
{
	t_model			*model;
	unsigned int	i;

	i = 0;
	while (i < scene->m_model->size)
	{
		model = scene->m_model->model[i];
		if (model->index_shader >= scene->m_model->size)
		{
			return (dprintf(2, "Votre model %s doit avoir un index ou un \
				nom de shader valide.\n", model->name) && 0);
		}
		if (model->index_material >= scene->m_material->size)
		{
			return (dprintf(2, "Votre model %s doit avoir un index ou un \
				nom de materiaux valide.\n", model->name) && 0);
		}
		i++;
	}
	return (true);
}

static bool		scene_require_zero_size(t_scene *scene)
{
	if (!scene->m_model->size)
	{
		return (ft_bool_error("La Scene a besoin d'au moins d'un Model",
			NULL, NULL));
	}
	if (!scene->m_shader->size)
	{
		return (ft_bool_error("La Scene a besoin d'au moins d'un Shader",
			NULL, NULL));
	}
	if (!scene->m_material->size)
	{
		return (ft_bool_error("La Scene a besoin d'au moins d'un Material",
			NULL, NULL));
	}
	return (true);
}

bool			scene_require(t_scene *scene)
{
	if (!scene_require_zero_size(scene))
		return (false);
	if (scene->m_light->size > SCOP_MAX_LIGHTS)
		return (ft_bool_error("La Scene a trop de lights", NULL, NULL));
	if (scene->m_model->size > SCOP_MAX_MODEL)
		return (ft_bool_error("La Scene a trop de models", NULL, NULL));
	if (scene->m_material->size > SCOP_MAX_MATERIAL)
		return (ft_bool_error("La Scene a trop de materials", NULL, NULL));
	if (!scene->m_light->size)
		return (ft_bool_error("La Scene a pas de light", NULL, NULL));
	if (scene->m_shader->size > SCOP_MAX_SHADER)
		return (ft_bool_error("La Scene a trop de shader", NULL, NULL));
	if (!scene_require_index_m_model(scene))
		return (false);
	return (true);
}
