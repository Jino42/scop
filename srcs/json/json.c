#include "scop.h"
#include <cJSON.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static bool			json_parse_vector(cJSON *vector_json, t_vector *vector)
{
	cJSON	*current;

	if (!vector_json)
		return (false);
	current = cJSON_GetObjectItemCaseSensitive(vector_json, "x");
	if (!cJSON_IsNumber(current))
		return (false);
	vector->x = current->valuedouble;
	current = cJSON_GetObjectItemCaseSensitive(vector_json, "y");
	if (!cJSON_IsNumber(current))
		return (false);
	vector->y = current->valuedouble;
	current = cJSON_GetObjectItemCaseSensitive(vector_json, "z");
	if (!cJSON_IsNumber(current))
		return (false);
	vector->z = current->valuedouble;

	return (true);
}

static bool			json_parse_vector_single_float(cJSON *vector_json, t_vector *vector)
{
	if (!vector_json)
		return (false);
	if (!cJSON_IsNumber(vector_json))
		return (false);
	vector->x = vector_json->valuedouble;
	vector->y = vector_json->valuedouble;
	vector->z = vector_json->valuedouble;
	return (true);
}

bool			json_parse_float(cJSON *source, float *dest)
{
	if (!source)
		return (false);
	if (!cJSON_IsNumber(source))
		return (false);
	*dest  = source->valuedouble;
	return (true);
}


static bool			json_load_src(const char *path, char *buffer)
{
	int		fd;

	if (!(fd = open(path, O_RDONLY)))
		return (false);
	read(fd, buffer, MAX_SOURCE_SIZE);
	close(fd);
	return (true);
}

bool		json_verif_material(cJSON *json)
{
	cJSON *material;
	t_vector vector;

	vector = vector_construct(1.f, 1.f, 1.f);
	cJSON *materials = cJSON_GetObjectItemCaseSensitive(json, "materials");

	material = materials->child;
	while (material)
    {
        cJSON *name = cJSON_GetObjectItemCaseSensitive(material, "name");

        if (!cJSON_IsString(name) || name->valuestring == NULL)
        {
			printf("WTF 1\n");
        }

		if (!json_parse_vector(cJSON_GetObjectItemCaseSensitive(material, "diffuse"), &vector) &&
			!json_parse_vector_single_float(cJSON_GetObjectItemCaseSensitive(material, "diffuse"), &vector))
			return (false);
		printf("Diffuse: %.2f %.2f %.2f\n", vector.x, vector.y, vector.z);
		material = material->next;
    }
	return (true);
}

bool				temp_json(void)
{
	char			buffer[MAX_SOURCE_SIZE];
	cJSON			*materials;

	bzero(buffer, MAX_SOURCE_SIZE);
	json_load_src("./json/materials.json", buffer);
	printf("%s\n", buffer);
	materials = cJSON_Parse(buffer);
	if (materials == NULL)
		return (ft_bool_error(NULL, &json_error, NULL));
	printf("%s\n", buffer);
	json_verif_material(materials);
	return (true);
}
