/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_model_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:46:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/18 20:11:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool			m_model_json_loop_parse_2(t_scene *scene,
												t_model *model,
												cJSON *json_model,
												int index)
{
	t_vector		tmp;

	if (json_parse_vector(json_model, "scaling", &tmp))
	{
		model->scaling = tmp;
		model->same_scaling = tmp.x;
	}
	if (!json_parse_vector(json_model, "rotation", &model->rotation))
	{
		return (dprintf(2, "JSON model[%i] %s : rotation error\n",
				index, model->name) == 0);
	}
	if (!(m_model_json_parse_shader(json_model, "shader", scene, model)))
	{
		return (dprintf(2, "JSON model[%i] %s : shader error\n",
				index, model->name) == 0);
	}
	if (!(m_model_json_parse_material(json_model, "material", scene, model)))
	{
		return (dprintf(2, "JSON model[%i] %s : shader error\n",
				index, model->name) == 0);
	}
	return (true);
}

static bool			m_model_json_loop_parse(t_scene *scene,
												t_m_model *m_model,
												cJSON *json_model,
												int index)
{
	char			*str[2];
	t_model			*model;

	bzero(str, sizeof(char *) * 2);
	if (!json_parse_string(json_model, "path", &str[0]))
	{
		return (dprintf(2, "JSON model[%i]: the path is Undefined\n",
				index) == 0);
	}
	if (!json_parse_string(json_model, "name", &str[1]))
	{
		return (dprintf(2, "JSON model[%i]: the name is Undefined\n",
				index) == 0);
	}
	if (!(model = m_model_load(m_model, scene->m_material, str[0], str[1])))
	{
		return (dprintf(2, "JSON model[%i]: Load model Failed\n",
				index) == 0);
	}
	if (!json_parse_vector(json_model, "position", &model->position))
	{
		return (dprintf(2, "JSON model[%i] %s : position error\n",
				index, model->name) == 0);
	}
	return (m_model_json_loop_parse_2(scene, model, json_model, index));
}

static bool			m_model_json_loop(t_scene *scene,
										t_m_model *m_model,
										cJSON *json_models)
{
	int				index;
	cJSON			*json_model;

	if (!json_models)
		return (ft_bool_error("JSON models is undefined ", NULL, NULL));
	json_model = json_models->child;
	index = 0;
	while (json_model)
	{
		if (!m_model_json_loop_parse(scene, m_model, json_model, index))
			return (false);
		json_model = json_model->next;
		index++;
	}
	return (true);
}

bool				m_model_json_parse(t_scene *scene,
									t_m_model *m_model,
									cJSON *get,
									const char *key)
{
	cJSON	*source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!(m_model_json_loop(scene, m_model, source)))
	{
		return (ft_bool_error("Erreur: Le parsing de t_m_model a échoué",
				NULL, NULL));
	}
	return (true);
}
