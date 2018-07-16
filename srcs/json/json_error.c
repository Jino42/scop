#include <stdio.h>
#include <cJSON.h>
#include <stdbool.h>

bool json_error(void *ptr)
{
	if (ptr)
		(void)ptr;
	printf("Error JSON parse: %s\n", cJSON_GetErrorPtr());
	return (true);
}
