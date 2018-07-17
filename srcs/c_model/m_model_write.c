/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_model_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:46:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 17:15:42 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	m_model_json_write_one(t_model *model, cJSON *json_models)
{
	cJSON			*json_model;

	if (!(json_model = cJSON_CreateObject()))
		return (false);
	cJSON_AddItemToArray(json_models, json_model);
	if (!json_add_string(json_model, "name", model->name) ||
		!json_add_string(json_model, "path", model->path))
		return (false);
	if (!json_add_int(json_model, "material", model->index_material) ||
		!json_add_int(json_model, "shader", model->index_shader))
		return (false);
	if (!json_add_vector(json_model, "position", &model->position) ||
		!json_add_vector(json_model, "rotation", &model->rotation) ||
		!json_add_vector(json_model, "scaling", &model->scaling))
		return (false);
	return (true);
}

bool		m_model_json_write(t_m_model *m_model, cJSON *json_scene)
{
	cJSON			*json_models;
	unsigned int	i;

	if (!(json_models = cJSON_CreateArray()))
		return (false);
	cJSON_AddItemToObject(json_scene, "model", json_models);
	i = 0;
	while (i < m_model->size)
	{
		if (!m_model_json_write_one(m_model->model[i], json_models))
			return (false);
		i++;
	}
	return (true);
}
