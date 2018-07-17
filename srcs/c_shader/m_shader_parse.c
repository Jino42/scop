/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shader_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:26:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:41:12 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool		m_shader_json_loop_parse(t_m_shader *m_shader,
											cJSON *json_shader,
											int index)
{
	char			*str[3];

	bzero(str, sizeof(char **) * 3);
	if (!json_parse_string(json_shader, "vertex", &str[0]))
	{
		return (dprintf(2, "JSON shader[%i]: the vertex shader is Undefined\n",
				index) == 0);
	}
	if (!json_parse_string(json_shader, "fragment", &str[1]))
	{
		return (dprintf(2, "JSON shader[%i]: the fragment shader is \
				Undefined\n", index) == 0);
	}
	if (!json_parse_string(json_shader, "name", &str[2]))
	{
		return (dprintf(2, "JSON shader[%i]: the name is Undefined\n",
				index) == 0);
	}
	if (!(m_shader->add(m_shader, str[0], str[1], str[2])))
		return (false);
	return (true);
}

static bool		m_shader_json_loop(t_m_shader *m_shader, cJSON *json_shaders)
{
	int				index;
	cJSON			*json_shader;

	if (!json_shaders)
		return (ft_bool_error("JSON shaders is undefined ", NULL, NULL));
	json_shader = json_shaders->child;
	index = 0;
	while (json_shader)
	{
		if (!m_shader_json_loop_parse(m_shader, json_shader, index))
			return (false);
		json_shader = json_shader->next;
		index++;
	}
	return (true);
}

bool			m_shader_json_parse(t_m_shader *m_shader,
									cJSON *get,
									const char *key)
{
	cJSON	*source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!(m_shader_json_loop(m_shader, source)))
	{
		return (ft_bool_error("Erreur: Le parsing de t_m_shader a échoué",
			NULL, NULL));
	}
	return (true);
}
