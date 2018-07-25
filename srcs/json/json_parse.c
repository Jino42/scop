/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:32:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/25 17:18:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool			json_parse_vector_xyz(cJSON *get,
										const char *key,
										t_vector *vector)
{
	cJSON	*current;
	cJSON	*source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!source)
		return (false);
	current = cJSON_GetObjectItemCaseSensitive(source, "x");
	if (!cJSON_IsNumber(current))
		return (false);
	vector->x = current->valuedouble;
	current = cJSON_GetObjectItemCaseSensitive(source, "y");
	if (!cJSON_IsNumber(current))
		return (false);
	vector->y = current->valuedouble;
	current = cJSON_GetObjectItemCaseSensitive(source, "z");
	if (!cJSON_IsNumber(current))
		return (false);
	vector->z = current->valuedouble;
	return (true);
}

bool			json_parse_vector_single_float(cJSON *get,
												const char *key,
												t_vector *vector)
{
	cJSON *source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!source)
		return (false);
	if (!cJSON_IsNumber(source))
		return (false);
	vector->x = source->valuedouble;
	vector->y = source->valuedouble;
	vector->z = source->valuedouble;
	return (true);
}

bool			json_parse_vector(cJSON *get, const char *key, t_vector *vector)
{
	if (!json_parse_vector_xyz(get, key, vector)
		&& !json_parse_vector_single_float(get, key, vector))
		return (false);
	return (true);
}

bool			json_parse_float(cJSON *get, const char *key, float *dest)
{
	cJSON *source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!source)
		return (false);
	if (!cJSON_IsNumber(source))
		return (false);
	*dest = source->valuedouble;
	return (true);
}

bool			json_parse_string(cJSON *get, const char *key, char **dest)
{
	cJSON *source;

	source = cJSON_GetObjectItemCaseSensitive(get, key);
	if (!source)
		return (false);
	if (!cJSON_IsString(source) || !source->valuestring)
		return (false);
	*dest = source->valuestring;
	return (true);
}
