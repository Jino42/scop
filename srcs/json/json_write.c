#include "scop.h"

bool		json_add_string(cJSON *json, char *key, char *value)
{
	cJSON			*item;

	if (!(item = cJSON_CreateString(value)))
		return (false);
	cJSON_AddItemToObject(json, key, item);
	return (true);
}

bool		json_add_int(cJSON *json, char *key, int value)
{
	cJSON			*item;

	if (!(item = cJSON_CreateNumber(value)))
		return (false);
	cJSON_AddItemToObject(json, key, item);
	return (true);
}

bool		json_add_float(cJSON *json, char *key, float value)
{
	cJSON			*item;

	if (!(item = cJSON_CreateNumber(value)))
		return (false);
	cJSON_AddItemToObject(json, key, item);
	return (true);
}

bool		json_add_vector(cJSON *json, char *key, t_vector *value)
{
	cJSON			*item;
	cJSON			*json_vector;

	if (!(json_vector = cJSON_CreateObject()))
		return (false);
	cJSON_AddItemToObject(json, key, json_vector);

	item = cJSON_CreateNumber(value->x);
	cJSON_AddItemToObject(json_vector, "x", item);

	item = cJSON_CreateNumber(value->y);
	cJSON_AddItemToObject(json_vector, "y", item);

	item = cJSON_CreateNumber(value->z);
	cJSON_AddItemToObject(json_vector, "z", item);
	return (true);
}
