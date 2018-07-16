#include "scop.h"
#include <cJSON.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool			json_parse_vector_xyz(cJSON *get, const char *key, t_vector *vector)
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

bool			json_parse_vector_single_float(cJSON *get, const char *key, t_vector *vector)
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
	if (!json_parse_vector_xyz(get, key, vector) && !json_parse_vector_single_float(get, key, vector))
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
	*dest  = source->valuedouble;
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
	*dest  = source->valuestring;
	return (true);
}

cJSON			*json_load_src(const char *path, char *buffer)
{
	cJSON	*ptr;
	int		fd;

	if (!(fd = open(path, O_RDONLY)))
		return (NULL);
	read(fd, buffer, MAX_SOURCE_SIZE);
	close(fd);
	ptr = cJSON_Parse(buffer);
	if (!ptr)
		json_error(NULL);
	return (ptr);
}
