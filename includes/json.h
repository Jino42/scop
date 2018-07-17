#ifndef JSON_H
# define JSON_H

# include <stdbool.h>
# include "cJSON.h"

bool			json_error(void *ptr);
bool			json_parse_vector_xyz(cJSON *vector_json, const char *key, t_vector *vector);
bool			json_parse_vector_single_float(cJSON *vector_json, const char *key, t_vector *vector);
bool			json_parse_vector(cJSON *vector_json, const char *key, t_vector *vector);
bool			json_parse_float(cJSON *source, const char *key, float *dest);
bool			json_parse_string(cJSON *get, const char *key, char **dest);
cJSON			*json_load_src(const char *path, char *buffer);


bool			json_add_vector(cJSON *json, char *key, t_vector *value);
bool			json_add_int(cJSON *json, char *key, int value);
bool			json_add_float(cJSON *json, char *key, float value);
bool			json_add_string(cJSON *json, char *key, char *value);

#endif
