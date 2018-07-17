#include "scop.h"

bool json_error(void *ptr)
{
	if (ptr)
		(void)ptr;
	printf("Error JSON parse: %s\n", cJSON_GetErrorPtr());
	return (true);
}
